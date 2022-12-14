// Generated by the protocol buffer compiler.  DO NOT EDIT!
// source: ProxyLoginReq.proto

#ifndef GOOGLE_PROTOBUF_INCLUDED_ProxyLoginReq_2eproto
#define GOOGLE_PROTOBUF_INCLUDED_ProxyLoginReq_2eproto

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
#define PROTOBUF_INTERNAL_EXPORT_ProxyLoginReq_2eproto
PROTOBUF_NAMESPACE_OPEN
namespace internal {
class AnyMetadata;
}  // namespace internal
PROTOBUF_NAMESPACE_CLOSE

// Internal implementation detail -- do not use these members.
struct TableStruct_ProxyLoginReq_2eproto {
  static const uint32_t offsets[];
};
extern const ::PROTOBUF_NAMESPACE_ID::internal::DescriptorTable descriptor_table_ProxyLoginReq_2eproto;
namespace Protocol {
class ProxyLoginReq;
struct ProxyLoginReqDefaultTypeInternal;
extern ProxyLoginReqDefaultTypeInternal _ProxyLoginReq_default_instance_;
}  // namespace Protocol
PROTOBUF_NAMESPACE_OPEN
template<> ::Protocol::ProxyLoginReq* Arena::CreateMaybeMessage<::Protocol::ProxyLoginReq>(Arena*);
PROTOBUF_NAMESPACE_CLOSE
namespace Protocol {

// ===================================================================

class ProxyLoginReq final :
    public ::PROTOBUF_NAMESPACE_ID::Message /* @@protoc_insertion_point(class_definition:Protocol.ProxyLoginReq) */ {
 public:
  inline ProxyLoginReq() : ProxyLoginReq(nullptr) {}
  ~ProxyLoginReq() override;
  explicit PROTOBUF_CONSTEXPR ProxyLoginReq(::PROTOBUF_NAMESPACE_ID::internal::ConstantInitialized);

  ProxyLoginReq(const ProxyLoginReq& from);
  ProxyLoginReq(ProxyLoginReq&& from) noexcept
    : ProxyLoginReq() {
    *this = ::std::move(from);
  }

  inline ProxyLoginReq& operator=(const ProxyLoginReq& from) {
    CopyFrom(from);
    return *this;
  }
  inline ProxyLoginReq& operator=(ProxyLoginReq&& from) noexcept {
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
  static const ProxyLoginReq& default_instance() {
    return *internal_default_instance();
  }
  static inline const ProxyLoginReq* internal_default_instance() {
    return reinterpret_cast<const ProxyLoginReq*>(
               &_ProxyLoginReq_default_instance_);
  }
  static constexpr int kIndexInFileMessages =
    0;

  friend void swap(ProxyLoginReq& a, ProxyLoginReq& b) {
    a.Swap(&b);
  }
  inline void Swap(ProxyLoginReq* other) {
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
  void UnsafeArenaSwap(ProxyLoginReq* other) {
    if (other == this) return;
    GOOGLE_DCHECK(GetOwningArena() == other->GetOwningArena());
    InternalSwap(other);
  }

  // implements Message ----------------------------------------------

  ProxyLoginReq* New(::PROTOBUF_NAMESPACE_ID::Arena* arena = nullptr) const final {
    return CreateMaybeMessage<ProxyLoginReq>(arena);
  }
  using ::PROTOBUF_NAMESPACE_ID::Message::CopyFrom;
  void CopyFrom(const ProxyLoginReq& from);
  using ::PROTOBUF_NAMESPACE_ID::Message::MergeFrom;
  void MergeFrom( const ProxyLoginReq& from) {
    ProxyLoginReq::MergeImpl(*this, from);
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
  void InternalSwap(ProxyLoginReq* other);

  private:
  friend class ::PROTOBUF_NAMESPACE_ID::internal::AnyMetadata;
  static ::PROTOBUF_NAMESPACE_ID::StringPiece FullMessageName() {
    return "Protocol.ProxyLoginReq";
  }
  protected:
  explicit ProxyLoginReq(::PROTOBUF_NAMESPACE_ID::Arena* arena,
                       bool is_message_owned = false);
  public:

  static const ClassData _class_data_;
  const ::PROTOBUF_NAMESPACE_ID::Message::ClassData*GetClassData() const final;

  ::PROTOBUF_NAMESPACE_ID::Metadata GetMetadata() const final;

  // nested types ----------------------------------------------------

  // accessors -------------------------------------------------------

  enum : int {
    kServerTypeFieldNumber = 1,
  };
  // int32 serverType = 1;
  void clear_servertype();
  int32_t servertype() const;
  void set_servertype(int32_t value);
  private:
  int32_t _internal_servertype() const;
  void _internal_set_servertype(int32_t value);
  public:

  // @@protoc_insertion_point(class_scope:Protocol.ProxyLoginReq)
 private:
  class _Internal;

  template <typename T> friend class ::PROTOBUF_NAMESPACE_ID::Arena::InternalHelper;
  typedef void InternalArenaConstructable_;
  typedef void DestructorSkippable_;
  struct Impl_ {
    int32_t servertype_;
    mutable ::PROTOBUF_NAMESPACE_ID::internal::CachedSize _cached_size_;
  };
  union { Impl_ _impl_; };
  friend struct ::TableStruct_ProxyLoginReq_2eproto;
};
// ===================================================================


// ===================================================================

#ifdef __GNUC__
  #pragma GCC diagnostic push
  #pragma GCC diagnostic ignored "-Wstrict-aliasing"
#endif  // __GNUC__
// ProxyLoginReq

// int32 serverType = 1;
inline void ProxyLoginReq::clear_servertype() {
  _impl_.servertype_ = 0;
}
inline int32_t ProxyLoginReq::_internal_servertype() const {
  return _impl_.servertype_;
}
inline int32_t ProxyLoginReq::servertype() const {
  // @@protoc_insertion_point(field_get:Protocol.ProxyLoginReq.serverType)
  return _internal_servertype();
}
inline void ProxyLoginReq::_internal_set_servertype(int32_t value) {
  
  _impl_.servertype_ = value;
}
inline void ProxyLoginReq::set_servertype(int32_t value) {
  _internal_set_servertype(value);
  // @@protoc_insertion_point(field_set:Protocol.ProxyLoginReq.serverType)
}

#ifdef __GNUC__
  #pragma GCC diagnostic pop
#endif  // __GNUC__

// @@protoc_insertion_point(namespace_scope)

}  // namespace Protocol

// @@protoc_insertion_point(global_scope)

#include <google/protobuf/port_undef.inc>
#endif  // GOOGLE_PROTOBUF_INCLUDED_GOOGLE_PROTOBUF_INCLUDED_ProxyLoginReq_2eproto
