#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::VertexBuffer
	
    Interface level class for vertex buffers
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/vertexbuffer.h"
#include "types.h"
namespace JARVIS {
namespace Metal
{
class Context;
class VertexBuffer : public Base::VertexBuffer
{
    __ClassDecl(VertexBuffer);
public:
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
private:
    friend class Metal::Context;
    
    OBJC_ID_POINTER(MTLBuffer) buffer;
};

}} // namespace JARVIS::Metal