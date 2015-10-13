#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::VertexBuffer
	
    Interface level class for vertex buffers
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/vertexbuffer.h"
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
    
private:
    friend class Metal::Context;
    
    /// initialize an index buffer which can be resized
    void InitMutable(const InitList<VertexComponent>& comps, const uint32 size, const byte* data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency);
    /// initialize an index buffer which is immutable
    void InitImmutable(const InitList<VertexComponent>& comps, const uint32 size, const byte* data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency, Render::ImmutableFlags flags);
    
    OBJC_ID_POINTER(MTLBuffer) buffer;
};

}} // namespace JARVIS::Metal