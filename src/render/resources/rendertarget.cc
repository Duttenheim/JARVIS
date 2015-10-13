//------------------------------------------------------------------------------
/**
    @class JARVIS::Render::RenderTarget
 	(C) 2015 See the LICENSE file.
*/
#include "rendertarget.h"
#include "../texture.h"
#include "../depthstenciltarget.h"
namespace JARVIS {
namespace Base
{
    
//------------------------------------------------------------------------------
/**
*/
RenderTarget::RenderTarget() :
    isWindowTarget(false)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
RenderTarget::~RenderTarget()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
RenderTarget::InitWithTargets(const InitList<Ptr<Render::Texture>>& textures, const Ptr<Render::DepthStencilTarget>& depthStencil)
{
    this->textures = textures;
    this->depthStencilTarget = depthStencilTarget;
}

//------------------------------------------------------------------------------
/**
*/
void
RenderTarget::InitWithWindow(const Ptr<Render::Window> &window)
{
    // do nothing
}

}} // namespace JARVIS::Base
