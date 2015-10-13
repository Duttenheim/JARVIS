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
    viewport(nullptr)
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
RenderTarget::InitWithTargets(const InitList<Ptr<Render::Texture>>& textures, const Ptr<Render::DepthStencilTarget>& depthStencil)
{
    Base::RenderTarget::InitWithTargets(Core::Forward(textures), Core::Forward(depthStencil));
    this->pass = [MTLRenderPassDescriptor alloc];
    
    int32 i;
    for (i = 0; i < this->textures.Size(); i++)
    {
        MTLRenderPassColorAttachmentDescriptor* desc = [this->pass.colorAttachments objectAtIndexedSubscript:i];
        desc.texture = this->textures[i]->texture;
        desc.loadAction = MTLLoadActionClear;
        desc.clearColor = MTLClearColorMake(0.0f, 1.0f, 0.0f, 0.0f);
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
    Base::RenderTarget::InitWithWindow(Core::Forward(window));
    this->pass = window->view.currentRenderPassDescriptor;

    // setup viewport, sin
    this->viewport = new MTLViewport;
    this->viewport->originX = 0;
    this->viewport->originY = 0;
    this->viewport->width = this->textures[0]->width;
    this->viewport->height = this->textures[0]->height;
}

}} // namespace JARVIS::Metal
