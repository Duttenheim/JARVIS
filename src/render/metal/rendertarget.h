#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::RenderTarget
	
    Metal implementation of a render target
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/rendertarget.h"
#include "types.h"
namespace JARVIS {
namespace Metal
{
class Context;
class PipelineState;

class RenderTarget : public Base::RenderTarget
{
    __ClassDecl(RenderTarget);
public:
    /// constructor
    RenderTarget();
    /// destructor
    virtual ~RenderTarget();
    
    /// setup render target from list of textures and optional depth-stencil target
    void InitWithTargets(InitList<Ptr<Render::Texture>> textures, const Ptr<Render::DepthStencilTarget>& depthStencil);
    /// setup render target from window
    void InitWithWindow(const Ptr<Render::Window>& window);
    
    /// retrieve render pass for this frame
    OBJC_POINTER(MTLRenderPassDescriptor) GetPass();
    
private:
    friend class Metal::Context;
    friend class Metal::PipelineState;
    OBJC_POINTER(MTLViewport) viewport;
    OBJC_POINTER(MTLRenderPassDescriptor) pass;
    OBJC_POINTER(MTKView) view;
};


}} // namespace JARVIS::Metal