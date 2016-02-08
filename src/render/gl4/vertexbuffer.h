#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::VertexBuffer
	
    Implements what is known in OpenGL as an array buffer.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/vertexbuffer.h"
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
    void InitMutable(const InitList<VertexComponent>& comps, const uint32 size, const byte* data, AccessPattern access, UsagePattern usage, FrequencyPattern frequency);
    /// initialize an index buffer which is immutable
    void InitImmutable(const InitList<VertexComponent>& comps, const uint32 size, const byte* data, AccessPattern access, UsagePattern usage, FrequencyPattern frequency, ImmutableFlags flags);
    
private:
    GLuint handle;  
};

}} // namespace JARVIS::GL4