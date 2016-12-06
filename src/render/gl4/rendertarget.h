#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::RenderTarget
	
    Implements an OpenGL renderable surface (or multiple) 
    which is called an FBO, or Framebuffer Object.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/rendertarget.h"


namespace JARVIS {
namespace GL4
{
class RenderTarget : public Base::RenderTarget
{
    __ClassDecl(RenderTarget);
public:
    /// constructor
    RenderTarget();
    /// destructor
    virtual ~RenderTarget();
    
    /// setup render target from list of textures and optional depth-stencil target
    void Setup(const InitList<Ptr<Render::Texture>>& textures, const Ptr<Render::DepthStencilTarget>& depthStencil);
    /// setup render target from window
    void Setup(const Ptr<Render::Window>& window);

    
private:
    GLuint fbo;
};

}} // namespace JARVIS::GL4