#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Base::DepthStencilTarget
	
    Base class for depth-stencil renderable targets
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Base
{
class DepthStencilTarget : public Core::Ref
{
    __ClassDecl(DepthStencilTarget);
public:
    /// constructor
    DepthStencilTarget();
    /// destructor
    virtual ~DepthStencilTarget();
    
private:
};

}} // namespace JARVIS::Base