#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::VertexBuffer
	
    Interface level class for vertex buffers
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "buffer.h"
#include "util/array.h"
#include "resources/vertextypes.h"
namespace JARVIS {
namespace Base
{    
class VertexBuffer : public Buffer
{
    __ClassDecl(VertexBuffer);
public:

    struct VertexComponent
    {
        uint32 size;
        uint32 offset;
        Render::ComponentType type;
    };
    
    /// constructor
    VertexBuffer();
    /// destructor
    virtual ~VertexBuffer();
    
    /// bind to render pipeline
    void Bind(uint32& componentIndex);
    
    /// initialize an index buffer which can be resized
    void InitMutable(InitList<VertexComponent> comps, const uint32 size, const byte* data, Render::AccessPattern access = Render::AccessPattern::None, Render::UsagePattern usage = Render::UsagePattern::CPUWriteGPURead, Render::FrequencyPattern frequency = Render::FrequencyPattern::ChangeOnceUseMany);
    /// initialize an index buffer which is immutable
    void InitImmutable(InitList<VertexComponent> comps, const uint32 size, const byte* data, Render::AccessPattern access = Render::AccessPattern::None, Render::UsagePattern usage = Render::UsagePattern::CPUWriteGPURead, Render::FrequencyPattern frequency = Render::FrequencyPattern::ChangeOnceUseMany, Render::ImmutableFlags flags = Render::ImmutableFlags::None);
protected:
    
    Core::Array<VertexComponent> components;
    uint32 vertexByteSize;
};

//------------------------------------------------------------------------------
/**
*/
inline void
VertexBuffer::InitMutable(InitList<JARVIS::Base::VertexBuffer::VertexComponent> comps, const uint32 size, const byte* data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency)
{
    Buffer::InitMutable(Render::BufferType::VertexBufferType, size, data, access, usage, frequency);
    this->components = comps;
    this->vertexByteSize = 0;
    int32 i;
    for (i = 0; i < this->components.Size(); i++)
    {
        this->components[i].offset = this->vertexByteSize;
        this->vertexByteSize += this->components[i].size;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline void
VertexBuffer::InitImmutable(InitList<JARVIS::Base::VertexBuffer::VertexComponent> comps, const uint32 size, const byte* data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency, Render::ImmutableFlags flags)
{
    Buffer::InitImmutable(Render::BufferType::VertexBufferType, size, data, access, usage, frequency, flags);
    this->components = comps;
    this->vertexByteSize = 0;
    int32 i;
    for (i = 0; i < this->components.Size(); i++)
    {
        this->vertexByteSize += this->components[i].size;
    }
}

}} // namespace JARVIS::Render