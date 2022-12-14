// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: GoldUpdatedEvent.proto

#include "GoldUpdatedEvent.pb.h"

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

namespace Protocol {
PROTOBUF_CONSTEXPR GoldUpdateEvent::GoldUpdateEvent(
    ::_pbi::ConstantInitialized): _impl_{
    /*decltype(_impl_.gold_)*/0
  , /*decltype(_impl_._cached_size_)*/{}} {}
struct GoldUpdateEventDefaultTypeInternal {
  PROTOBUF_CONSTEXPR GoldUpdateEventDefaultTypeInternal()
      : _instance(::_pbi::ConstantInitialized{}) {}
  ~GoldUpdateEventDefaultTypeInternal() {}
  union {
    GoldUpdateEvent _instance;
  };
};
PROTOBUF_ATTRIBUTE_NO_DESTROY PROTOBUF_CONSTINIT PROTOBUF_ATTRIBUTE_INIT_PRIORITY1 GoldUpdateEventDefaultTypeInternal _GoldUpdateEvent_default_instance_;
}  // namespace Protocol
static ::_pb::Metadata file_level_metadata_GoldUpdatedEvent_2eproto[1];
static constexpr ::_pb::EnumDescriptor const** file_level_enum_descriptors_GoldUpdatedEvent_2eproto = nullptr;
static constexpr ::_pb::ServiceDescriptor const** file_level_service_descriptors_GoldUpdatedEvent_2eproto = nullptr;

const uint32_t TableStruct_GoldUpdatedEvent_2eproto::offsets[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  ~0u,  // no _has_bits_
  PROTOBUF_FIELD_OFFSET(::Protocol::GoldUpdateEvent, _internal_metadata_),
  ~0u,  // no _extensions_
  ~0u,  // no _oneof_case_
  ~0u,  // no _weak_field_map_
  ~0u,  // no _inlined_string_donated_
  PROTOBUF_FIELD_OFFSET(::Protocol::GoldUpdateEvent, _impl_.gold_),
};
static const ::_pbi::MigrationSchema schemas[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) = {
  { 0, -1, -1, sizeof(::Protocol::GoldUpdateEvent)},
};

static const ::_pb::Message* const file_default_instances[] = {
  &::Protocol::_GoldUpdateEvent_default_instance_._instance,
};

const char descriptor_table_protodef_GoldUpdatedEvent_2eproto[] PROTOBUF_SECTION_VARIABLE(protodesc_cold) =
  "\n\026GoldUpdatedEvent.proto\022\010Protocol\"\037\n\017Go"
  "ldUpdateEvent\022\014\n\004gold\030\001 \001(\005b\006proto3"
  ;
static ::_pbi::once_flag descriptor_table_GoldUpdatedEvent_2eproto_once;
const ::_pbi::DescriptorTable descriptor_table_GoldUpdatedEvent_2eproto = {
    false, false, 75, descriptor_table_protodef_GoldUpdatedEvent_2eproto,
    "GoldUpdatedEvent.proto",
    &descriptor_table_GoldUpdatedEvent_2eproto_once, nullptr, 0, 1,
    schemas, file_default_instances, TableStruct_GoldUpdatedEvent_2eproto::offsets,
    file_level_metadata_GoldUpdatedEvent_2eproto, file_level_enum_descriptors_GoldUpdatedEvent_2eproto,
    file_level_service_descriptors_GoldUpdatedEvent_2eproto,
};
PROTOBUF_ATTRIBUTE_WEAK const ::_pbi::DescriptorTable* descriptor_table_GoldUpdatedEvent_2eproto_getter() {
  return &descriptor_table_GoldUpdatedEvent_2eproto;
}

// Force running AddDescriptors() at dynamic initialization time.
PROTOBUF_ATTRIBUTE_INIT_PRIORITY2 static ::_pbi::AddDescriptorsRunner dynamic_init_dummy_GoldUpdatedEvent_2eproto(&descriptor_table_GoldUpdatedEvent_2eproto);
namespace Protocol {

// ===================================================================

class GoldUpdateEvent::_Internal {
 public:
};

GoldUpdateEvent::GoldUpdateEvent(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                         bool is_message_owned)
  : ::PROTOBUF_NAMESPACE_ID::Message(arena, is_message_owned) {
  SharedCtor(arena, is_message_owned);
  // @@protoc_insertion_point(arena_constructor:Protocol.GoldUpdateEvent)
}
GoldUpdateEvent::GoldUpdateEvent(const GoldUpdateEvent& from)
  : ::PROTOBUF_NAMESPACE_ID::Message() {
  GoldUpdateEvent* const _this = this; (void)_this;
  new (&_impl_) Impl_{
      decltype(_impl_.gold_){}
    , /*decltype(_impl_._cached_size_)*/{}};

  _internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
  _this->_impl_.gold_ = from._impl_.gold_;
  // @@protoc_insertion_point(copy_constructor:Protocol.GoldUpdateEvent)
}

inline void GoldUpdateEvent::SharedCtor(
    ::_pb::Arena* arena, bool is_message_owned) {
  (void)arena;
  (void)is_message_owned;
  new (&_impl_) Impl_{
      decltype(_impl_.gold_){0}
    , /*decltype(_impl_._cached_size_)*/{}
  };
}

GoldUpdateEvent::~GoldUpdateEvent() {
  // @@protoc_insertion_point(destructor:Protocol.GoldUpdateEvent)
  if (auto *arena = _internal_metadata_.DeleteReturnArena<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>()) {
  (void)arena;
    return;
  }
  SharedDtor();
}

inline void GoldUpdateEvent::SharedDtor() {
  GOOGLE_DCHECK(GetArenaForAllocation() == nullptr);
}

void GoldUpdateEvent::SetCachedSize(int size) const {
  _impl_._cached_size_.Set(size);
}

void GoldUpdateEvent::Clear() {
// @@protoc_insertion_point(message_clear_start:Protocol.GoldUpdateEvent)
  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  _impl_.gold_ = 0;
  _internal_metadata_.Clear<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>();
}

const char* GoldUpdateEvent::_InternalParse(const char* ptr, ::_pbi::ParseContext* ctx) {
#define CHK_(x) if (PROTOBUF_PREDICT_FALSE(!(x))) goto failure
  while (!ctx->Done(&ptr)) {
    uint32_t tag;
    ptr = ::_pbi::ReadTag(ptr, &tag);
    switch (tag >> 3) {
      // int32 gold = 1;
      case 1:
        if (PROTOBUF_PREDICT_TRUE(static_cast<uint8_t>(tag) == 8)) {
          _impl_.gold_ = ::PROTOBUF_NAMESPACE_ID::internal::ReadVarint32(&ptr);
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

uint8_t* GoldUpdateEvent::_InternalSerialize(
    uint8_t* target, ::PROTOBUF_NAMESPACE_ID::io::EpsCopyOutputStream* stream) const {
  // @@protoc_insertion_point(serialize_to_array_start:Protocol.GoldUpdateEvent)
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  // int32 gold = 1;
  if (this->_internal_gold() != 0) {
    target = stream->EnsureSpace(target);
    target = ::_pbi::WireFormatLite::WriteInt32ToArray(1, this->_internal_gold(), target);
  }

  if (PROTOBUF_PREDICT_FALSE(_internal_metadata_.have_unknown_fields())) {
    target = ::_pbi::WireFormat::InternalSerializeUnknownFieldsToArray(
        _internal_metadata_.unknown_fields<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(::PROTOBUF_NAMESPACE_ID::UnknownFieldSet::default_instance), target, stream);
  }
  // @@protoc_insertion_point(serialize_to_array_end:Protocol.GoldUpdateEvent)
  return target;
}

size_t GoldUpdateEvent::ByteSizeLong() const {
// @@protoc_insertion_point(message_byte_size_start:Protocol.GoldUpdateEvent)
  size_t total_size = 0;

  uint32_t cached_has_bits = 0;
  // Prevent compiler warnings about cached_has_bits being unused
  (void) cached_has_bits;

  // int32 gold = 1;
  if (this->_internal_gold() != 0) {
    total_size += ::_pbi::WireFormatLite::Int32SizePlusOne(this->_internal_gold());
  }

  return MaybeComputeUnknownFieldsSize(total_size, &_impl_._cached_size_);
}

const ::PROTOBUF_NAMESPACE_ID::Message::ClassData GoldUpdateEvent::_class_data_ = {
    ::PROTOBUF_NAMESPACE_ID::Message::CopyWithSourceCheck,
    GoldUpdateEvent::MergeImpl
};
const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GoldUpdateEvent::GetClassData() const { return &_class_data_; }


void GoldUpdateEvent::MergeImpl(::PROTOBUF_NAMESPACE_ID::Message& to_msg, const ::PROTOBUF_NAMESPACE_ID::Message& from_msg) {
  auto* const _this = static_cast<GoldUpdateEvent*>(&to_msg);
  auto& from = static_cast<const GoldUpdateEvent&>(from_msg);
  // @@protoc_insertion_point(class_specific_merge_from_start:Protocol.GoldUpdateEvent)
  GOOGLE_DCHECK_NE(&from, _this);
  uint32_t cached_has_bits = 0;
  (void) cached_has_bits;

  if (from._internal_gold() != 0) {
    _this->_internal_set_gold(from._internal_gold());
  }
  _this->_internal_metadata_.MergeFrom<::PROTOBUF_NAMESPACE_ID::UnknownFieldSet>(from._internal_metadata_);
}

void GoldUpdateEvent::CopyFrom(const GoldUpdateEvent& from) {
// @@protoc_insertion_point(class_specific_copy_from_start:Protocol.GoldUpdateEvent)
  if (&from == this) return;
  Clear();
  MergeFrom(from);
}

bool GoldUpdateEvent::IsInitialized() const {
  return true;
}

void GoldUpdateEvent::InternalSwap(GoldUpdateEvent* other) {
  using std::swap;
  _internal_metadata_.InternalSwap(&other->_internal_metadata_);
  swap(_impl_.gold_, other->_impl_.gold_);
}

::PROTOBUF_NAMESPACE_ID::Metadata GoldUpdateEvent::GetMetadata() const {
  return ::_pbi::AssignDescriptors(
      &descriptor_table_GoldUpdatedEvent_2eproto_getter, &descriptor_table_GoldUpdatedEvent_2eproto_once,
      file_level_metadata_GoldUpdatedEvent_2eproto[0]);
}

// @@protoc_insertion_point(namespace_scope)
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> PROTOBUF_NOINLINE ::Protocol::GoldUpdateEvent*
Arena::CreateMaybeMessage< ::Protocol::GoldUpdateEvent >(Arena* arena) {
  return Arena::CreateMessageInternal< ::Protocol::GoldUpdateEvent >(arena);
}
PROTOBUF_NAMESPACE_CLOSE

// @@protoc_insertion_point(global_scope)
#include <google/protobuf/port_undef.inc>
