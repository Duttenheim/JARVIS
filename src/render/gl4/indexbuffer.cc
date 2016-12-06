//------------------------------------------------------------------------------
/**
    @class JARVIS::GL4::IndexBuffer
 	(C) 2015 See the LICENSE file.
*/
#include "indexbuffer.h"
namespace JARVIS {
namespace GL4
{
    
//------------------------------------------------------------------------------
/**
*/
IndexBuffer::IndexBuffer()
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
IndexBuffer::Bind()
{
    j_assert(this->handle != 0);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->handle);
}

//------------------------------------------------------------------------------
/**
*/
void
IndexBuffer::InitMutable(IndexBuffer::IndexType type, int32 numIndices, byte *data)
{
    Base::IndexBuffer::InitMutable(type, numIndices, data);
    glGenBuffers(1, &this->handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->handle);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, numIndices * (uint8)type, data, GL_STATIC_DRAW);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

//------------------------------------------------------------------------------
/**
*/
void
IndexBuffer::InitImmutable(IndexBuffer::IndexType type, int32 numIndices, byte *data)
{
    Base::IndexBuffer::InitImmutable(type, numIndices, data);
    glGenBuffers(1, &this->handle);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, this->handle);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
}

}} // namespace JARVIS::GL4
