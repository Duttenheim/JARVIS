#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Base::Buffer
	
    Base class for GPU-side buffers.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "buffertypes.h"
#include "resources/buffertypes.h"
namespace JARVIS {
namespace Base
{
class Buffer : public Core::Ref
{
    __ClassDecl(Buffer);
public:

    /// constructor
    Buffer();
    /// destructor
    virtual ~Buffer();
    
protected:
    /// initialize buffer which can be resized
    void InitMutable(Render::BufferType type, const int32 size, const byte* data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency);
    /// initialize buffer which is immutable and cannot be resized
    void InitImmutable(Render::BufferType type, const int32 size, const byte* data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency, Render::ImmutableFlags flags);
    
    /// buffer data
    void BufferData(int32 size, void* data);
    
    Render::BufferType type;
    Render::StorageType storage;
    Render::AccessPattern access;
    Render::UsagePattern usage;
    Render::FrequencyPattern frequency;
    Render::ImmutableFlags flags;
};

//------------------------------------------------------------------------------
/**
*/
inline void
Buffer::InitMutable(Render::BufferType type, const int32 size, const byte *data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency)
{
    j_assert(this->storage != Render::StorageType::Immutable);
    this->type = type;
    this->storage = Render::StorageType::Mutable;
    this->access = access;
    this->usage = usage;
    this->frequency = frequency;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Buffer::InitImmutable(Render::BufferType type, const int32 size, const byte *data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency, Render::ImmutableFlags flags)
{
    j_assert(this->storage != Render::StorageType::Immutable);
    this->type = type;
    this->storage = Render::StorageType::Immutable;
    this->access = access;
    this->usage = usage;
    this->frequency = frequency;
    this->flags = flags;
}

}} // namespace JARVIS::Base