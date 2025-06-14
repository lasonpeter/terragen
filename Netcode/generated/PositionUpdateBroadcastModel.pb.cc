// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: PositionUpdateBroadcastModel.proto

#include "PositionUpdateBroadcastModel.pb.h"

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
PROTOBUF_CONSTEXPR PositionUpdateBroadcastModel::PositionUpdateBroadcastModel(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.playername_)*/{&::_pbi::fixed_address_empty_string, ::_pbi::ConstantInitialized{}}
  , /*decltype(_impl_.x_)*/0
  , /*decltype(_impl_.y_)*/0
  , /*decltype(_impl_.z_)*/0
  , /*decltype(_impl_.rotationx_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct PositionUpdateBroadcastModelDefaultTypeInternal {
  PROTOBUF_CONSTEXPR PositionUpdateBroadcastModelDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~PositionUpdateBroadcastModelDefaultTypeInternal() {}
  union {
    PositionUpdateBroadcastModel _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 PositionUpdateBroadcastModelDefaultTypeInternal _PositionUpdateBroadcastModel_default_instance_;
}  // namespace terragen
static ::_pb::Metadata file_level_metadata_PositionUpdateBroadcastModel_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_PositionUpdateBroadcastModel_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_PositionUpdateBroadcastModel_2eproto = nullptr;

const uint32_t TableStruct_PositionUpdateBroadcastModel_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::terragen::PositionUpdateBroadcastModel, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::terragen::PositionUpdateBroadcastModel, _impl_.playername_),
  PROTOBUF_FIELD_OFFSET(::terragen::PositionUpdateBroadcastModel, _impl_.x_),
  PROTOBUF_FIELD_OFFSET(::terragen::PositionUpdateBroadcastModel, _impl_.y_),
  PROTOBUF_FIELD_OFFSET(::terragen::PositionUpdateBroadcastModel, _impl_.z_),
  PROTOBUF_FIELD_OFFSET(::terragen::PositionUpdateBroadcastModel, _impl_.rotationx_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::terragen::PositionUpdateBroadcastModel)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::terragen::_PositionUpdateBroadcastModel_default_instance_._instance,
};

const char descriptor_table_protodef_PositionUpdateBroadcastModel_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\"PositionUpdateBroadcastModel.proto\022\010te"
  "rragen\"f\n\034PositionUpdateBroadcastModel\022\022"
  "\n\nplayerName\030\001 \001(\t\022\t\n\001x\030\002 \001(\002\022\t\n\001y\030\003 \001(\002"
  "\022\t\n\001z\030\004 \001(\002\022\021\n\trotationX\030\005 \001(\002b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_PositionUpdateBroadcastModel_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_PositionUpdateBroadcastModel_2eproto = {
    false, false, 158, descriptor_table_protodef_PositionUpdateBroadcastModel_2eproto,
    "PositionUpdateBroadcastModel.proto",
    &descriptor_table_PositionUpdateBroadcastModel_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_PositionUpdateBroadcastModel_2eproto::offsets,
    file_level_metadata_PositionUpdateBroadcastModel_2eproto, file_level_enum_descriptors_PositionUpdateBroadcastModel_2eproto,
    file_level_service_descriptors_PositionUpdateBroadcastModel_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_PositionUpdateBroadcastModel_2eproto_getter() {
  return &descriptor_table_PositionUpdateBroadcastModel_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_PositionUpdateBroadcastModel_2eproto(&descriptor_table_PositionUpdateBroadcastModel_2eproto);
namespace terragen {

// ===================================================================

class PositionUpdateBroadcastModel::_Internal {
 public:
};

PositionUpdateBroadcastModel::PositionUpdateBroadcastModel(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:terragen.PositionUpdateBroadcastModel)
}
PositionUpdateBroadcastModel::PositionUpdateBroadcastModel(const PositionUpdateBroadcastModel& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  PositionUpdateBroadcastModel* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.playername_){}
    , decltype(_impl_.x_){}
    , decltype(_impl_.y_){}
    , decltype(_impl_.z_){}
    , decltype(_impl_.rotationx_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _impl_.playername_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.playername_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
  if (!from._internal_playername().empty()) {
    _this->_impl_.playername_.Set(from._internal_playername(), 
      _this->GetArenaForAllocation());
  }
  ::memcpy(&_impl_.x_, &from._impl_.x_,
    static_cast<size_t>(reinterpret_cast<char*>(&_impl_.rotationx_) -
    reinterpret_cast<char*>(&_impl_.x_)) + sizeof(_impl_.rotationx_));
  // @@protoc_insertion_point(copy_constructor:terragen.PositionUpdateBroadcastModel)
}

inline void PositionUpdateBroadcastModel::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.playername_){}
    , decltype(_impl_.x_){0}
    , decltype(_impl_.y_){0}
    , decltype(_impl_.z_){0}
    , decltype(_impl_.rotationx_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
  _impl_.playername_.InitDefault();
  #ifdef PROTOBUF_FORCE_COPY_DEFAULT_STRING
    _impl_.playername_.Set("", GetArenaForAllocation());
  #endif // PROTOBUF_FORCE_COPY_DEFAULT_STRING
}

PositionUpdateBroadcastModel::~PositionUpdateBroadcastModel() {
  // @@protoc_insertion_point(destructor:terragen.PositionUpdateBroadcastModel)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void PositionUpdateBroadcastModel::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
  _impl_.playername_.Destroy();
}

void PositionUpdateBroadcastModel::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void PositionUpdateBroadcastModel::Clear() {
// @@protoc_insertion_point(message_clear_start:terragen.PositionUpdateBroadcastModel)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.playername_.ClearToEmpty();
  ::memset(&_impl_.x_, 0, static_cast<size_t>(
      reinterpret_cast<char*>(&_impl_.rotationx_) -
      reinterpret_cast<char*>(&_impl_.x_)) + sizeof(_impl_.rotationx_));
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* PositionUpdateBroadcastModel::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // string playerName = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 10)) {
          auto str = _internal_mutable_playername();
          ptr = ::_pbi::InlineGreedyStringParser(str, ptr, ctx);
          CHK_(ptr);
          CHK_(::_pbi::VerifyUTF8(str, "terragen.PositionUpdateBroadcastModel.playerName"));
        } else
          goto handle_unusual;
        continue;
      // float x = 2;
      case 2:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 21)) {
          _impl_.x_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float y = 3;
      case 3:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 29)) {
          _impl_.y_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float z = 4;
      case 4:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 37)) {
          _impl_.z_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
        } else
          goto handle_unusual;
        continue;
      // float rotationX = 5;
      case 5:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 45)) {
          _impl_.rotationx_ = ::PROTOBUF_NAMESPACE_ID::internal::UnalignedLoad<float>(ptr);
          ptr += sizeof(float);
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

uint8_t* PositionUpdateBroadcastModel::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:terragen.PositionUpdateBroadcastModel)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // string playerName = 1;
  if (!this->_internal_playername().empty()) {
    ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::VerifyUtf8String(
      this->_internal_playername().data(), static_cast<int>(this->_internal_playername().length()),
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::SERIALIZE,
      "terragen.PositionUpdateBroadcastModel.playerName");
    target = stream->WriteStringMaybeAliased(
        1, this->_internal_playername(), target);
  }

  // float x = 2;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = this->_internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(2, this->_internal_x(), target);
  }

  // float y = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = this->_internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(3, this->_internal_y(), target);
  }

  // float z = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_z = this->_internal_z();
  uint32_t raw_z;
  memcpy(&raw_z, &tmp_z, sizeof(tmp_z));
  if (raw_z != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(4, this->_internal_z(), target);
  }

  // float rotationX = 5;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_rotationx = this->_internal_rotationx();
  uint32_t raw_rotationx;
  memcpy(&raw_rotationx, &tmp_rotationx, sizeof(tmp_rotationx));
  if (raw_rotationx != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteFloatToArray(5, this->_internal_rotationx(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:terragen.PositionUpdateBroadcastModel)
  return target;
}

size_t PositionUpdateBroadcastModel::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:terragen.PositionUpdateBroadcastModel)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // string playerName = 1;
  if (!this->_internal_playername().empty()) {
    total_size += 1 +
      ::PROTOBUF_NAMESPACE_ID::internal::WireFormatLite::StringSize(
        this->_internal_playername());
  }

  // float x = 2;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = this->_internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    total_size += 1 + 4;
  }

  // float y = 3;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = this->_internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    total_size += 1 + 4;
  }

  // float z = 4;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_z = this->_internal_z();
  uint32_t raw_z;
  memcpy(&raw_z, &tmp_z, sizeof(tmp_z));
  if (raw_z != 0) {
    total_size += 1 + 4;
  }

  // float rotationX = 5;
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_rotationx = this->_internal_rotationx();
  uint32_t raw_rotationx;
  memcpy(&raw_rotationx, &tmp_rotationx, sizeof(tmp_rotationx));
  if (raw_rotationx != 0) {
    total_size += 1 + 4;
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData PositionUpdateBroadcastModel::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    PositionUpdateBroadcastModel::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*PositionUpdateBroadcastModel::GetClassData() const { return &_class_data_; }


void PositionUpdateBroadcastModel::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<PositionUpdateBroadcastModel*>(&to_msg);
  auto& from = static_cast<const PositionUpdateBroadcastModel&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:terragen.PositionUpdateBroadcastModel)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (!from._internal_playername().empty()) {
    _this->_internal_set_playername(from._internal_playername());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_x = from._internal_x();
  uint32_t raw_x;
  memcpy(&raw_x, &tmp_x, sizeof(tmp_x));
  if (raw_x != 0) {
    _this->_internal_set_x(from._internal_x());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_y = from._internal_y();
  uint32_t raw_y;
  memcpy(&raw_y, &tmp_y, sizeof(tmp_y));
  if (raw_y != 0) {
    _this->_internal_set_y(from._internal_y());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_z = from._internal_z();
  uint32_t raw_z;
  memcpy(&raw_z, &tmp_z, sizeof(tmp_z));
  if (raw_z != 0) {
    _this->_internal_set_z(from._internal_z());
  }
  static_assert(sizeof(uint32_t) == sizeof(float), "Code assumes uint32_t and float are the same size.");
  float tmp_rotationx = from._internal_rotationx();
  uint32_t raw_rotationx;
  memcpy(&raw_rotationx, &tmp_rotationx, sizeof(tmp_rotationx));
  if (raw_rotationx != 0) {
    _this->_internal_set_rotationx(from._internal_rotationx());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void PositionUpdateBroadcastModel::CopyFrom(const PositionUpdateBroadcastModel& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:terragen.PositionUpdateBroadcastModel)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool PositionUpdateBroadcastModel::IsInitialized() const {
  return true;
}

void PositionUpdateBroadcastModel::InternalSwap(PositionUpdateBroadcastModel* other) {
  using std::swap;
  auto* lhs_arena = GetArenaForAllocation();
  auto* rhs_arena = other->GetArenaForAllocation();
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  ::PROTOBUF_NAMESPACE_ID::internal::ArenaStringPtr::InternalSwap(
      &_impl_.playername_, lhs_arena,
      &other->_impl_.playername_, rhs_arena
  );
  ::PROTOBUF_NAMESPACE_ID::internal::memswap<
      PROTOBUF_FIELD_OFFSET(PositionUpdateBroadcastModel, _impl_.rotationx_)
      + sizeof(PositionUpdateBroadcastModel::_impl_.rotationx_)
      - PROTOBUF_FIELD_OFFSET(PositionUpdateBroadcastModel, _impl_.x_)>(
          reinterpret_cast<char*>(&_impl_.x_),
          reinterpret_cast<char*>(&other->_impl_.x_));
}

::PROTOBUF_NAMESPACE_ID::Metadata PositionUpdateBroadcastModel::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_PositionUpdateBroadcastModel_2eproto_getter, &descriptor_table_PositionUpdateBroadcastModel_2eproto_once,
      file_level_metadata_PositionUpdateBroadcastModel_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace terragen
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::terragen::PositionUpdateBroadcastModel*
Arena::CreateMaybeMessage< ::terragen::PositionUpdateBroadcastModel >(Arena* arena) {
  return Arena::CreateMessageInternal< ::terragen::PositionUpdateBroadcastModel >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
