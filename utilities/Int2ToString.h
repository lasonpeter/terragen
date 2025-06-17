//
// Created by xenu on 11/06/2025.
//

#ifndef TERRAGEN_INT2TOSTRING_H
#define TERRAGEN_INT2TOSTRING_H


#include <string>
#include "Mathf.h"

class Int2ToString {
    public:
    static std::string to_string(Int2 int2){
        return std::to_string(int2.x) + "_" + std::to_string(int2.y);
    }
};


#endif //TERRAGEN_INT2TOSTRING_H
