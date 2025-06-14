// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: LoginRespondModel.proto

#include "LoginRespondModel.pb.h"

#include <algorithm>

#include <google/protobuf/io/coded_stream.h>
#include <google/protobuf/extension_set.h>
#include <google/protobuf/wire_format_lite.h>
#include <google/protobuf/descriptor.h>
#include <google/protobuf/generated_message_reflection.h>
#include <google/protobuf/reflection_ops.h>
#include <google/protobuf/wire_format.h>
// @@protoc_insertion_point(includes)
#include <google/protobuf/port_def.inc>

PROTOBUF_PRAGMA_INIT_SEG

namespace _pb = ::PROTOBUF_NAMESPACE_ID;
namespace _pbi = _pb::internal;

namespace terragen {
PROTOBUF_CONSTEXPR LoginRespondModel::LoginRespondModel(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.success_)*/false
  , /*decltype(_impl_.udpport_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct LoginRespondModelDefaultTypeInternal {
  PROTOBUF_CONSTEXPR LoginRespondModelDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~LoginRespondModelDefaultTypeInternal() {}
  union {
    LoginRespondModel _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 LoginRespondModelDefaultTypeInternal _LoginRespondModel_default_instance_;
}  // namespace terragen
static ::_pb::Metadata file_level_metadata_LoginRespondModel_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_LoginRespondModel_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_LoginRespondModel_2eproto = nullptr;

const uint32_t TableStruct_LoginRespondModel_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::terragen::LoginRespondModel, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::terragen::LoginRespondModel, _impl_.success_),
  PROTOBUF_FIELD_OFFSET(::terragen::LoginRespondModel, _impl_.udpport_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::terragen::LoginRespondModel)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::terragen::_LoginRespondModel_default_instance_._instance,
};

const char descriptor_table_protodef_LoginRespondModel_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\027LoginRespondModel.proto\022\010terragen\"5\n\021L"
  "oginRespondModel\022\017\n\007success\030\001 \001(\010\022\017\n\007udp"
  "Port\030\002 \001(\005b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_LoginRespondModel_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_LoginRespondModel_2eproto = {
    false, false, 98, descriptor_table_protodef_LoginRespondModel_2eproto,
    "LoginRespondModel.proto",
    &descriptor_table_LoginRespondModel_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_LoginRespondModel_2eproto::offsets,
    file_level_metadata_LoginRespondModel_2eproto, file_level_enum_descriptors_LoginRespondModel_2eproto,
    file_level_service_descriptors_LoginRespondModel_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_LoginRespondModel_2eproto_getter() {
  return &descriptor_table_LoginRespondModel_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_LoginRespondModel_2eproto(&descriptor_table_LoginRespondModel_2eproto);
namespace terragen {

// ===================================================================

class LoginRespondModel::_Internal {
 public:
};

LoginRespondModel::LoginRespondModel(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:terragen.LoginRespondModel)
}
LoginRespondModel::LoginRespondModel(const LoginRespondModel& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  LoginRespondModel* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.success_){}
    , decltype(_impl_.udpport_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  ::memcpy(&_impl_.success_, &from._impl_.success_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.udpport_) -
    reinterpret_cast<char*>(&_impl_.success_)) + sizeof(_impl_.udpport_));
  // @@protoc_insertion_point(copy_constructor:terragen.LoginRespondModel)
}

inline void LoginRespondModel::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.success_){false}
    , decltype(_impl_.udpport_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

LoginRespondModel::~LoginRespondModel() {
  // @@protoc_insertion_point(destructor:terragen.LoginRespondModel)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void LoginRespondModel::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void LoginRespondModel::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void LoginRespondModel::Clear() {
// @@protoc_insertion_point(message_clear_start:terragen.LoginRespondModel)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  ::memset(&_impl_.success_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.udpport_) -
      reinterpret_cast<char*>(&_impl_.success_)) + sizeof(_impl_.udpport_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* LoginRespondModel::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // bool success = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.success_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint64(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      // int32 udpPort = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 16)) {
          _impl_.udpport_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
          CHK_(ptr);
        } else
          goto handle_unusual;
        continue;
      default:
        goto handle_unusual;
    }  // switch
  handle_unusual:
    if ((tag == 0) || ((tag & 7) == 4)) {
      CHK_(ptr);
      ctx->SetLastTag(tag);
      goto message_done;
    }
    ptr = UnknownFieldParse(
        tag,
        _internal_metadata_.mutable_unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(),
        ptr, ctx);
    CHK_(ptr != nullptr);
  }  // while
message_done:
  return ptr;
failure:
  ptr = nullptr;
  goto message_done;
#undef CHK_
}

uint8_t* LoginRespondModel::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:terragen.LoginRespondModel)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // bool success = 1;
  if (this->_internal_success() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteBoolToArray(1, this->_internal_success(), target);
  }

  // int32 udpPort = 2;
  if (this->_internal_udpport() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(2, this->_internal_udpport(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:terragen.LoginRespondModel)
  return target;
}

size_t LoginRespondModel::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:terragen.LoginRespondModel)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // bool success = 1;
  if (this->_internal_success() != 0) {
    total_size += 1 + 1;
  }

  // int32 udpPort = 2;
  if (this->_internal_udpport() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_udpport());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData LoginRespondModel::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    LoginRespondModel::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*LoginRespondModel::GetClassData() const { return &_class_data_; }


void LoginRespondModel::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<LoginRespondModel*>(&to_msg);
  auto& from = static_cast<const LoginRespondModel&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:terragen.LoginRespondModel)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_success() != 0) {
    _this->_internal_set_success(from._internal_success());
  }
  if (from._internal_udpport() != 0) {
    _this->_internal_set_udpport(from._internal_udpport());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void LoginRespondModel::CopyFrom(const LoginRespondModel& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:terragen.LoginRespondModel)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool LoginRespondModel::IsInitialized() const {
  return true;
}

void LoginRespondModel::InternalSwap(LoginRespondModel* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(LoginRespondModel, _impl_.udpport_)
      + sizeof(LoginRespondModel::_impl_.udpport_)
      - PROTOBUF_FIELD_OFFSET(LoginRespondModel, _impl_.success_)>(
          reinterpret_cast<char*>(&_impl_.success_),
          reinterpret_cast<char*>(&other->_impl_.success_));
}

::PROTOBUF_NAMESPACE_ID::Metadata LoginRespondModel::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_LoginRespondModel_2eproto_getter, &descriptor_table_LoginRespondModel_2eproto_once,
      file_level_metadata_LoginRespondModel_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace terragen
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::terragen::LoginRespondModel*
Arena::CreateMaybeMessage< ::terragen::LoginRespondModel >(Arena* arena) {
  return Arena::CreateMessageInternal< ::terragen::LoginRespondModel >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
