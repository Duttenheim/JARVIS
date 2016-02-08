//------------------------------------------------------------------------------
/**
    @class JARVIS::GL4::RenderTarget
 	(C) 2015 See the LICENSE file.
*/
#include "rendertarget.h"
#include "../texture.h"
#include "../depthstenciltarget.h"
namespace JARVIS {
namespace GL4
{
    
//------------------------------------------------------------------------------
/**
*/
RenderTarget::RenderTarget()
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
RenderTarget::Setup(const InitList<Ptr<Render::Texture>>& textures, const Ptr<Render::DepthStencilTarget>& depthStencil)
{
    Base::RenderTarget::Setup(textures, depthStencil);
    glGenFramebuffers(1, &this->fbo);
    glBindFramebuffer(GL_FRAMEBUFFER, this->fbo);
    int32 i;
    for (i = 0; i < this->textures.Size(); i++)
    {
        glFramebufferTexture(GL_FRAMEBUFFER, GL_COLOR_ATTACHMENT0 + i, this->textures[i]->handle, 0);
    }
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

//------------------------------------------------------------------------------
/**
*/
void
RenderTarget::Setup(const Ptr<Render::Window> &window)
{
    Base::RenderTarget::Setup(window);
    this->fbo = 0;
}


}} // namespace JARVIS::GL4
