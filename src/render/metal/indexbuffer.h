#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::IndexBuffer
	
    Metal implementation of an index buffer
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/indexbuffer.h"
#include "types.h"
namespace JARVIS {
namespace Metal
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
    
    /// initialize an index buffer which can be resized
    void InitMutable(IndexType type, int32 numIndices, byte* data);
    /// initialize an index buffer which is immutable
    void InitImmutable(IndexType type, int32 numIndices, byte* data);
private:
    friend class Context;
    OBJC_ID_POINTER(MTLBuffer) buffer;
};

}} // namespace JARVIS::Metal