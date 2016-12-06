//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::UniformBuffer
 	(C) 2015 See the LICENSE file.
*/
#include "uniformbuffer.h"
#include "../context.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
UniformBuffer::UniformBuffer()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
UniformBuffer::~UniformBuffer()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Create uniform buffer using a memory layout
*/
void
UniformBuffer::InitWithLayout(const InitList<UniformBuffer::LayoutMember> &layout)
{
    uint32 size = 0;
    uint32 i;
    for (i = 0; i < layout.size(); i++)
    {
        const UniformBuffer::LayoutMember& member = layout.begin()[i];
        UniformMember var;
        var.offset = size;
        var.size = member.size;
        this->offsetMap.Insert(member.identifier, var);
        size += member.size;
    }
    
    // create buffer
    MTLResourceOptions options = Types::BufferUsageFlag(Render::UsagePattern::CPUWriteGPURead, Render::ImmutableFlags(Render::ImmutableFlags::Persistent | Render::ImmutableFlags::Coherent));
    this->buffer = [Context::Current->device newBufferWithLength:size options:options];
    this->mapped = (uint8*)[this->buffer contents];
}

//------------------------------------------------------------------------------
/**
    Create uniform buffer without any specific memory layout
*/
void
UniformBuffer::InitWithSize(uint32 size)
{
    // create buffer
    MTLResourceOptions options = Types::BufferUsageFlag(Render::UsagePattern::CPUWriteGPURead, Render::ImmutableFlags(Render::ImmutableFlags::Persistent | Render::ImmutableFlags::Coherent));
    this->buffer = [Context::Current->device newBufferWithLength:size options:options];
    this->mapped = (uint8*)[this->buffer contents];
}

//------------------------------------------------------------------------------
/**
*/
void
UniformBuffer::Update(const UniformBuffer::UniformMember &member, void *data, uint32 size)
{
    // perform a memcpy to buffer
    memcpy(this->mapped + member.offset, data, size);
}
}} // namespace JARVIS::Metal
