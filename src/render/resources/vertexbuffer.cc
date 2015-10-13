//------------------------------------------------------------------------------
/**
    @class JARVIS::Render::VertexBuffer
 	(C) 2015 See the LICENSE file.
*/
#include "vertexbuffer.h"
namespace JARVIS {
namespace Base
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
    // empty, override in subclass
}

}} // namespace JARVIS::Base
