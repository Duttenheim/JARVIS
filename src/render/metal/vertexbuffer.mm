//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::VertexBuffer
 	(C) 2015 See the LICENSE file.
*/
#include "vertexbuffer.h"
#include "../context.h"
#include "types.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
VertexBuffer::VertexBuffer()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
VertexBuffer::~VertexBuffer()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
VertexBuffer::Bind(uint32& componentIndex)
{
    // hmm, this function has no function, huh...
}

//------------------------------------------------------------------------------
/**
*/
void
VertexBuffer::InitMutable(const InitList<VertexComponent>& comps, const uint32 size, const byte* data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency)
{
    MTLResourceOptions options = Types::BufferUsageFlag(usage, Render::ImmutableFlags::None);
    this->buffer = [Context::Current->device newBufferWithBytes:data length:size options:options];
}

//------------------------------------------------------------------------------
/**
*/
void
VertexBuffer::InitImmutable(const InitList<VertexComponent>& comps, const uint32 size, const byte* data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency, Render::ImmutableFlags flags)
{
    MTLResourceOptions options = Types::BufferUsageFlag(usage, flags);
    this->buffer = [Context::Current->device newBufferWithBytes:data length:size options:options];
}

}} // namespace JARVIS::Metal
