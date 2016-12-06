//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::RenderTarget
 	(C) 2015 See the LICENSE file.
*/
#include "rendertarget.h"
#include "../window.h"
#include "../texture.h"
#include "../depthstenciltarget.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
RenderTarget::RenderTarget() :
    viewport(nil),
    pass(nil),
    view(nil)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
RenderTarget::~RenderTarget()
{
    if (this->viewport != nullptr) delete this->viewport;
}

//------------------------------------------------------------------------------
/**
*/
void
RenderTarget::InitWithTargets(InitList<Ptr<Render::Texture>> textures, const Ptr<Render::DepthStencilTarget>& depthStencil)
{
    Base::RenderTarget::InitWithTargets(textures, depthStencil);
    this->pass = [MTLRenderPassDescriptor renderPassDescriptor];
    this->view = nil;
    
    int32 i;
    for (i = 0; i < this->textures.Size(); i++)
    {
        MTLRenderPassColorAttachmentDescriptor* desc = this->pass.colorAttachments[i];
        desc.texture = this->textures[i]->texture;
        desc.loadAction = MTLLoadActionClear;
        desc.clearColor = MTLClearColorMake(this->clearColors[i].x(), this->clearColors[i].y(), this->clearColors[i].z(), this->clearColors[i].w());
    }
    
    // ehh, Metal has a single viewport, and not one per target... Weird...
    this->viewport = new MTLViewport;
    this->viewport->originX = 0;
    this->viewport->originY = 0;
    this->viewport->width = this->textures[0]->width;
    this->viewport->height = this->textures[0]->height;
}

//------------------------------------------------------------------------------
/**
*/
void
RenderTarget::InitWithWindow(const Ptr<Render::Window>& window)
{
    Base::RenderTarget::InitWithWindow(window);
    this->pass = nil;
    this->view = window->view;
    
    // setup viewport, sin
    this->viewport = new MTLViewport;
    this->viewport->originX = 0;
    this->viewport->originY = 0;
    this->viewport->width = window->width;
    this->viewport->height = window->height;
}

//------------------------------------------------------------------------------
/**
*/
OBJC_POINTER(MTLRenderPassDescriptor)
RenderTarget::GetPass()
{
    // if we have a view, grab the current pass, and set it to clear...
    if (this->view != nil)
    {
        this->pass = this->view.currentRenderPassDescriptor;
        this->pass.colorAttachments[0].loadAction = MTLLoadActionClear;
        this->pass.colorAttachments[0].clearColor = MTLClearColorMake(this->clearColors[0].x(), this->clearColors[0].y(), this->clearColors[0].z(), this->clearColors[0].w());
    }
    return this->pass;
}

}} // namespace JARVIS::Metal
