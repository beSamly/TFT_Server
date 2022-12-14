// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: CreateHostResponse.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_CreateHostResponse_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_CreateHostResponse_2eproto

#include <limits>
#include <string>

#include <google/protobuf/port_def.inc>
#if PROTOBUF_VERSION < 3021000
#error This file was generated by a newer version of protoc which is
#error incompatible with your Protocol Buffer headers. Please update
#error your headers.
#endif
#if 3021001 < PROTOBUF_MIN_PROTOC_VERSION
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
#define PROTOBUF_INTERNAL_EXPORT_CreateHostResponse_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_CreateHostResponse_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_CreateHostResponse_2eproto;
namespace Protocol {
class CreateHostResponse;
struct CreateHostResponseDefaultTypeInternal;
extern CreateHostResponseDefaultTypeInternal _CreateHostResponse_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::CreateHostResponse* Arena::CreateMaybeMessage<::Protocol::CreateHostResponse>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class CreateHostResponse final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.CreateHostResponse) */ {
 public:
  inline CreateHostResponse() : CreateHostResponse(nullptr) {}
  ~CreateHostResponse() override;
  explicit PROTOBUF_CONSTEXPR CreateHostResponse(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  CreateHostResponse(const CreateHostResponse& from);
  CreateHostResponse(CreateHostResponse&& from) noexcept
    : CreateHostResponse() {
    *this = ::std::move(from);
  }

  inline CreateHostResponse& operator=(const CreateHostResponse& from) {
    CopyFrom(from);
    return *this;
  }
  inline CreateHostResponse& operator=(CreateHostResponse&& from) noexcept {
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
  static const CreateHostResponse& default_instance() {
    return *internal_default_instance();
  }
  static inline const CreateHostResponse* internal_default_instance() {
    return reinterpret_cast<const CreateHostResponse*>(
               &_CreateHostResponse_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(CreateHostResponse& a, CreateHostResponse& b) {
    a.Swap(&b);
  }
  inline void Swap(CreateHostResponse* other) {
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
  void UnsafeArenaSwap(CreateHostResponse* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  CreateHostResponse* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<CreateHostResponse>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const CreateHostResponse& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const CreateHostResponse& from) {
    CreateHostResponse::MergeImpl(*this, from);
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
  void InternalSwap(CreateHostResponse* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.CreateHostResponse";
  }
  protected:
  explicit CreateHostResponse(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kResultFieldNumber = 1,
    kMatchIdFieldNumber = 2,
  };
  // bool result = 1;
  void clear_result();
  bool result() const;
  void set_result(bool value);
  private:
  bool _internal_result() const;
  void _internal_set_result(bool value);
  public:

  // int32 matchId = 2;
  void clear_matchid();
  int32_t matchid() const;
  void set_matchid(int32_t value);
  private:
  int32_t _internal_matchid() const;
  void _internal_set_matchid(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.CreateHostResponse)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    bool result_;
    int32_t matchid_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_CreateHostResponse_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// CreateHostResponse

// bool result = 1;
inline void CreateHostResponse::clear_result() {
  _impl_.result_ = false;
}
inline bool CreateHostResponse::_internal_result() const {
  return _impl_.result_;
}
inline bool CreateHostResponse::result() const {
  // @@protoc_insertion_point(field_get:Protocol.CreateHostResponse.result)
  return _internal_result();
}
inline void CreateHostResponse::_internal_set_result(bool value) {
  
  _impl_.result_ = value;
}
inline void CreateHostResponse::set_result(bool value) {
  _internal_set_result(value);
  // @@protoc_insertion_point(field_set:Protocol.CreateHostResponse.result)
}

// int32 matchId = 2;
inline void CreateHostResponse::clear_matchid() {
  _impl_.matchid_ = 0;
}
inline int32_t CreateHostResponse::_internal_matchid() const {
  return _impl_.matchid_;
}
inline int32_t CreateHostResponse::matchid() const {
  // @@protoc_insertion_point(field_get:Protocol.CreateHostResponse.matchId)
  return _internal_matchid();
}
inline void CreateHostResponse::_internal_set_matchid(int32_t value) {
  
  _impl_.matchid_ = value;
}
inline void CreateHostResponse::set_matchid(int32_t value) {
  _internal_set_matchid(value);
  // @@protoc_insertion_point(field_set:Protocol.CreateHostResponse.matchId)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_CreateHostResponse_2eproto
