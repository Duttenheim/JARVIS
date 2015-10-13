#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::IndexBuffer
	
    Interface level implementation of an index buffer. 
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "buffer.h"
namespace JARVIS {
namespace Base
{
class IndexBuffer : public Buffer
{
    __ClassDecl(IndexBuffer);
public:

    enum class IndexType : uint8
    {
        UShort = 2,     // size is 2 bytes, just encode in enum value...
        UInt = 4        // size is 4 bytes, also encoded in enum value
    };
    
    /// constructor
    IndexBuffer();
    /// destructor
    virtual ~IndexBuffer();
    
    /// bind to be rendered
    void Bind();

protected:
    /// initialize an index buffer which can be resized
    void InitMutable(IndexType type, int32 numIndices, byte* data);
    /// initialize an index buffer which is immutable
    void InitImmutable(IndexType type, int32 numIndices, byte* data);
    
    int32 numIndices;
    IndexType indexType;
};

//------------------------------------------------------------------------------
/**
*/
inline void
IndexBuffer::InitMutable(IndexType type, int32 numIndices, byte *data)
{
    this->indexType = type;
    this->numIndices = numIndices;
}

//------------------------------------------------------------------------------
/**
*/
inline void
IndexBuffer::InitImmutable(IndexType type, int32 numIndices, byte *data)
{
    this->indexType = type;
    this->numIndices = numIndices;
}

}} // namespace JARVIS::Render