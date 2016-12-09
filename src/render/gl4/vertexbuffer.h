#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::VertexBuffer
	
    Implements what is known in OpenGL as an array buffer.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/vertexbuffer.h"
#include "types.h"
namespace JARVIS {
namespace GL4
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
    
    /// bind to be rendered
    void Bind(uint32& componentIndex);
    
private:
    friend class GL4::Context;
    
    /// initialize an index buffer which can be resized
    void InitMutable(const InitList<VertexComponent>& comps, const uint32 size, const byte* data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency);
    /// initialize an index buffer which is immutable
    void InitImmutable(const InitList<VertexComponent>& comps, const uint32 size, const byte* data, Render::AccessPattern access, Render::UsagePattern usage, Render::FrequencyPattern frequency, Render::ImmutableFlags flags);
    
private:
    GLuint handle;  
};

}} // namespace JARVIS::GL4