#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::RenderState
	
    Metal implementation of a render state (or pipeline object)
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "resources/renderstate.h"
#include "types.h"
namespace JARVIS {
namespace Metal
{
class Context;
class RenderState : public Base::RenderState
{
    __ClassDecl(RenderState);
public:
    /// constructor
    RenderState();
    /// destructor
    virtual ~RenderState();
    
    /// update implementation types when we end the change
    void Commit();
    
private:
    friend class Context;
    OBJC_ID_POINTER(MTLDepthStencilState) mtlDepthStencilState;
    OBJC_POINTER(MTLScissorRect) mtlScissorRect;
};

}} // namespace JARVIS::Metal