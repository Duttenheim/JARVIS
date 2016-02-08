#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::DepthStencilTarget
	
    Implements a depthstencil target in OpenGL.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/depthstenciltarget.h"
namespace JARVIS {
namespace GL4
{
class DepthStencilTarget : public Base::DepthStencilTarget
{
public:
    /// constructor
    DepthStencilTarget();
    /// destructor
    virtual ~DepthStencilTarget();
    
private:
};

}} // namespace JARVIS::GL4