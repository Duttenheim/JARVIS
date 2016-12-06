#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::RenderState
	
    Implements a container of the current render state, 
    which in OpenGL is set through several state switching calls.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/renderstate.h"
namespace JARVIS {
namespace GL4
{
class RenderState : public Base::RenderState
{
    __ClassDecl(RenderState);
public:
    /// constructor
    RenderState();
    /// destructor
    virtual ~RenderState();
    
private:
};

}} // namespace JARVIS::GL4