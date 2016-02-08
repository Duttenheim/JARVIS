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
    depthStencilTarget(nullptr),
    clearFlags(ClearFlags::Color | ClearFlags::Depth | ClearFlags::Stencil),
    samples(1),
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
RenderTarget::InitWithTargets(InitList<Ptr<Render::Texture>> textures, const Ptr<Render::DepthStencilTarget>& depthStencil)
{
    this->textures = textures;
    this->clearColors.Resize(this->textures.Size());
    this->clearColors.Fill(Math::Vec4(0, 1, 0, 0));
    this->depthStencilTarget = depthStencilTarget;
    this->isWindowTarget = false;
}

//------------------------------------------------------------------------------
/**
*/
void
RenderTarget::InitWithWindow(const Ptr<Render::Window> &window)
{
    this->clearColors.Resize(1);
    this->clearColors.Fill(Math::Vec4(1, 0, 0, 0));
    this->isWindowTarget = true;
}

}} // namespace JARVIS::Base
