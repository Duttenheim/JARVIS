#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::DepthStencilTarget
	
    Metal implementation of a depth-stencil target
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "resources/depthstenciltarget.h"
namespace JARVIS {
namespace Metal
{
class DepthStencilTarget : public Base::DepthStencilTarget
{
    __ClassDecl(DepthStencilTarget);
public:
    /// constructor
    DepthStencilTarget();
    /// destructor
    virtual ~DepthStencilTarget();
    
private:
};

}} // namespace JARVIS::Metal