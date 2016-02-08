#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::IndexBuffer
	
    Implements what is known in OpenGL as an element array buffer.
 
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/indexbuffer.h"
namespace JARVIS {
namespace GL4
{
class Context;
class IndexBuffer : public Base::IndexBuffer
{
    __ClassDecl(IndexBuffer);
public:
    /// constructor
    IndexBuffer();
    /// destructor
    virtual ~IndexBuffer();
    
    /// bind to be rendered
    void Bind();
    
private:
    friend class GL4::Context;

    /// initialize an index buffer which can be resized
    void InitMutable(IndexType type, int32 numIndices, byte* data);
    /// initialize an index buffer which is immutable
    void InitImmutable(IndexType type, int32 numIndices, byte* data);
    
    GLuint handle;
};

}} // namespace JARVIS::GL4