// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: LoginRespondModel.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_LoginRespondModel_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_LoginRespondModel_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021012 < PROTOBUF_MIN_PROTOC_VERSION
#error This file was generated by an older version of protoc which is
#error incompatible with your Protocol Buffer headers. Please
#error regenerate this file with a newer version of protoc.
#endif

#include <google/protobuf/port_undef.inc>
#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/arena.h>
#include <google/protobuf/arenastring.h>
#include <google/protobuf/generated_message_util.h>
#include <google/protobuf/metadata_lite.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/message.h>
#include <google/protobuf/repeated_field.h>  // IWYU pragma: export
#include <google/protobuf/extension_set.h>  // IWYU pragma: export
#include <google/protobuf/unknown_field_set.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>
#define PROTOBUF_INTERNAL_EXPORT_LoginRespondModel_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_LoginRespondModel_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_LoginRespondModel_2eproto;
namespace terragen {
class LoginRespondModel;
struct LoginRespondModelDefaultTypeInternal;
extern LoginRespondModelDefaultTypeInternal _LoginRespondModel_default_instance_;
}  // namespace terragen
PROTOBUF_NAMESPACE_OPEN
template<> ::terragen::LoginRespondModel* Arena::CreateMaybeMessage<::terragen::LoginRespondModel>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace terragen {

// ===================================================================

class LoginRespondModel final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:terragen.LoginRespondModel) */ {
 public:
  inline LoginRespondModel() : LoginRespondModel(nullptr) {}
  ~LoginRespondModel() override;
  explicit PROTOBUF_CONSTEXPR LoginRespondModel(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  LoginRespondModel(const LoginRespondModel& from);
  LoginRespondModel(LoginRespondModel&& from) noexcept
    : LoginRespondModel() {
    *this = ::std::move(from);
  }

  inline LoginRespondModel& operator=(const LoginRespondModel& from) {
    CopyFrom(from);
    return *this;
  }
  inline LoginRespondModel& operator=(LoginRespondModel&& from) noexcept {
    if (this == &from) return *this;
    if (GetOwningArena() == from.GetOwningArena()
  #ifdef PROTOBUF_FORCE_COPY_IN_MOVE
        && GetOwningArena() != nullptr
  #endif  // !PROTOBUF_FORCE_COPY_IN_MOVE
    ) {
      InternalSwap(&from);
    } else {
      CopyFrom(from);
    }
    return *this;
  }

  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* descriptor() {
    return GetDescriptor();
  }
  static const ::PROTOBUF_NAMESPACE_ID::Descriptor* GetDescriptor() {
    return default_instance().GetMetadata().descriptor;
  }
  static const ::PROTOBUF_NAMESPACE_ID::Reflection* GetReflection() {
    return default_instance().GetMetadata().reflection;
  }
  static const LoginRespondModel& default_instance() {
    return *internal_default_instance();
  }
  static inline const LoginRespondModel* internal_default_instance() {
    return reinterpret_cast<const LoginRespondModel*>(
               &_LoginRespondModel_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(LoginRespondModel& a, LoginRespondModel& b) {
    a.Swap(&b);
  }
  inline void Swap(LoginRespondModel* other) {
    if (other == this) return;
  #ifdef PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() != nullptr &&
        GetOwningArena() == other->GetOwningArena()) {
   #else  // PROTOBUF_FORCE_COPY_IN_SWAP
    if (GetOwningArena() == other->GetOwningArena()) {
  #endif  // !PROTOBUF_FORCE_COPY_IN_SWAP
      InternalSwap(other);
    } else {
      ::PROTOBUF_NAMESPACE_ID::internal::GenericSwap(this, other);
    }
  }
  void UnsafeArenaSwap(LoginRespondModel* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  LoginRespondModel* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<LoginRespondModel>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const LoginRespondModel& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const LoginRespondModel& from) {
    LoginRespondModel::MergeImpl(*this, from);
  }
  private:
  static void MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg);
  public:
  PROTOBUF_ATTRIBUTE_REINITIALIZES void Clear() final;
  bool IsInitialized() const final;

  size_t ByteSizeLong() const final;
  const char* _InternalParse(const char* ptr, ::PROTOBUF_NAMESPACE_ID::internal::ParseContext* ctx) final;
  uint8_t* _InternalSerialize(
      uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const final;
  int GetCachedSize() const final { return _impl_._cached_size_.Get(); }

  private:
  void SharedCtor(::PROTOBUF_NAMESPACE_ID::Arena* arena, bool is_message_owned);
  void SharedDtor();
  void SetCachedSize(int size) const final;
  void InternalSwap(LoginRespondModel* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "terragen.LoginRespondModel";
  }
  protected:
  explicit LoginRespondModel(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kSuccessFieldNumber = 1,
    kUdpPortFieldNumber = 2,
  };
  // bool success = 1;
  void clear_success();
  bool success() const;
  void set_success(bool value);
  private:
  bool _internal_success() const;
  void _internal_set_success(bool value);
  public:

  // int32 udpPort = 2;
  void clear_udpport();
  int32_t udpport() const;
  void set_udpport(int32_t value);
  private:
  int32_t _internal_udpport() const;
  void _internal_set_udpport(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:terragen.LoginRespondModel)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    bool success_;
    int32_t udpport_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_LoginRespondModel_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// LoginRespondModel

// bool success = 1;
inline void LoginRespondModel::clear_success() {
  _impl_.success_ = false;
}
inline bool LoginRespondModel::_internal_success() const {
  return _impl_.success_;
}
inline bool LoginRespondModel::success() const {
  // @@protoc_insertion_point(field_get:terragen.LoginRespondModel.success)
  return _internal_success();
}
inline void LoginRespondModel::_internal_set_success(bool value) {
  
  _impl_.success_ = value;
}
inline void LoginRespondModel::set_success(bool value) {
  _internal_set_success(value);
  // @@protoc_insertion_point(field_set:terragen.LoginRespondModel.success)
}

// int32 udpPort = 2;
inline void LoginRespondModel::clear_udpport() {
  _impl_.udpport_ = 0;
}
inline int32_t LoginRespondModel::_internal_udpport() const {
  return _impl_.udpport_;
}
inline int32_t LoginRespondModel::udpport() const {
  // @@protoc_insertion_point(field_get:terragen.LoginRespondModel.udpPort)
  return _internal_udpport();
}
inline void LoginRespondModel::_internal_set_udpport(int32_t value) {
  
  _impl_.udpport_ = value;
}
inline void LoginRespondModel::set_udpport(int32_t value) {
  _internal_set_udpport(value);
  // @@protoc_insertion_point(field_set:terragen.LoginRespondModel.udpPort)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace terragen

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_LoginRespondModel_2eproto
