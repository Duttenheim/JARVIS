//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::IndexBuffer
 	(C) 2015 See the LICENSE file.
*/
#include "indexbuffer.h"
#include "types.h"
#include "../context.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
IndexBuffer::IndexBuffer() :
    buffer(nullptr)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
IndexBuffer::~IndexBuffer()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
IndexBuffer::InitMutable(IndexBuffer::IndexType type, int32 numIndices, byte *data)
{
    Base::IndexBuffer::InitMutable(Fw(type), Fw(numIndices), Fw(data));
    MTLResourceOptions options = Types::BufferUsageFlag(usage, Render::ImmutableFlags::None);
    this->buffer = [Context::Current->device newBufferWithBytes:data length:numIndices * (type == IndexType::UInt ? 4 : 2) options:options];
}

//------------------------------------------------------------------------------
/**
*/
void
IndexBuffer::InitImmutable(IndexBuffer::IndexType type, int32 numIndices, byte *data)
{
    Base::IndexBuffer::InitImmutable(Fw(type), Fw(numIndices), Fw(data));
    MTLResourceOptions options = Types::BufferUsageFlag(usage, flags);
    this->buffer = [Context::Current->device newBufferWithBytes:data length:numIndices * (type == IndexType::UInt ? 4 : 2) options:options];
}

}} // namespace JARVIS::Metal
