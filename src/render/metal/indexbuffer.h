#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::IndexBuffer
	
    Metal implementation of an index buffer
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/indexbuffer.h"
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
    
private:
    friend class Context;
    OBJC_ID_POINTER(MTLBuffer) buffer;
};

}} // namespace JARVIS::Metal