#ifndef TERRAGEN_THREADPOOL_H
#define TERRAGEN_THREADPOOL_H

#include <vector>
#include <queue>
#include <thread>
#include <mutex>
#include <condition_variable>
#include <functional>
#include <future>

class ThreadPool {
public:
    explicit ThreadPool(size_t numThreads);
    ~ThreadPool();

    // Add a task to the thread pool
    template<class F, class... Args>
    auto enqueue(F&& f, Args&&... args) 
        -> std::future<typename std::invoke_result<F, Args...>::type>;

private:
    // Worker threads
    std::vector<std::thread> workers;
    
    // Task queue
    std::queue<std::function<void()>> tasks;
    
    // Synchronization
    std::mutex queueMutex;
    std::condition_variable condition;
    bool stop;
};

// Constructor - starts the thread pool
inline ThreadPool::ThreadPool(size_t numThreads) : stop(false) {
    for(size_t i = 0; i < numThreads; ++i) {
        workers.emplace_back([this] {
            while(true) {
                std::function<void()> task;
                
                {
                    std::unique_lock<std::mutex> lock(this->queueMutex);
                    
                    // Wait until we have a task or stop is signaled
                    this->condition.wait(lock, [this] { 
                        return this->stop || !this->tasks.empty(); 
                    });
                    
                    // Exit if the pool is stopping and there are no more tasks
                    if(this->stop && this->tasks.empty()) {
                        return;
                    }
                    
                    // Get the next task
                    task = std::move(this->tasks.front());
                    this->tasks.pop();
                }
                
                // Execute the task
                task();
            }
        });
    }
}

// Destructor - stops all threads
inline ThreadPool::~ThreadPool() {
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        stop = true;
    }
    
    condition.notify_all();
    
    // Join all threads
    for(std::thread &worker: workers) {
        if(worker.joinable()) {
            worker.join();
        }
    }
}

// Add a new task to the pool
template<class F, class... Args>
auto ThreadPool::enqueue(F&& f, Args&&... args) 
    -> std::future<typename std::invoke_result<F, Args...>::type> {
    
    using return_type = typename std::invoke_result<F, Args...>::type;
    
    // Create a shared pointer to the packaged task
    auto task = std::make_shared<std::packaged_task<return_type()>>(
        std::bind(std::forward<F>(f), std::forward<Args>(args)...)
    );
    
    // Get the future result before we move the task
    std::future<return_type> res = task->get_future();
    
    {
        std::unique_lock<std::mutex> lock(queueMutex);
        
        // Don't allow enqueueing after stopping the pool
        if(stop) {
            throw std::runtime_error("enqueue on stopped ThreadPool");
        }
        
        // Add the task to the queue
        tasks.emplace([task]() { (*task)(); });
    }
    
    // Wake up one thread to take the task
    condition.notify_one();
    
    return res;
}

#endif // TERRAGEN_THREADPOOL_H