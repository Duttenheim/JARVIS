#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::UniformBuffer
	
    Metal implementation of a uniform buffer
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "shading/uniformbuffer.h"
namespace JARVIS {
namespace Metal
{
class UniformBuffer : public Base::UniformBuffer
{
    __ClassDecl(UniformBuffer);
public:
    /// constructor
    UniformBuffer();
    /// destructor
    virtual ~UniformBuffer();
    
private:
};

}} // namespace JARVIS::Metal