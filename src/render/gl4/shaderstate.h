#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::ShaderInstance
	
    Implements a localized shader state, which is bound to a shader object,
    but provides it with variables.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "shading/shaderstate.h"
namespace JARVIS {
namespace GL4
{
class ShaderState : public Base::ShaderState
{
    __ClassDecl(ShaderState);
public:
    /// constructor
    ShaderState();
    /// destructor
    virtual ~ShaderState();
    
private:
};

}} // namespace JARVIS::GL4