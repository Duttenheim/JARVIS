#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::RenderTarget
	
    Interface level class for managing render targets.
 
    Window creates it's own render target which point directly to its screen surface.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "math/vec4.h"
namespace JARVIS {
namespace Render {
class Texture;
class DepthStencilTarget;
class Window;
}}

namespace JARVIS {
namespace Base
{
class RenderTarget : public Core::Ref
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

    /// set clear color, will also make color clearing active
    void SetClearColor(const uint8 texture, const Math::Vec4& color);
    /// set clear depth, will also make depth clearing active
    void SetClearDepth(const uint32 depth);
    /// set clear stencil, will also make depth clearing active
    void SetClearStencil(const uint32 stencil);
    /// set viewport
    void SetViewport(uint32 left, uint32 top, uint32 width, uint32 height);
    
protected:

    enum class ClearFlags : uint8
    {
        None = 1 << 0,
        Color = 1 << 1,
        Depth = 1 << 2,
        Stencil = 1 << 3
    };
    
    __ENUM_OR_OPERATOR(ClearFlags)
    
    Core::Array<Ptr<Render::Texture>> textures;
    Ptr<Render::DepthStencilTarget> depthStencilTarget;
    
    ClearFlags clearFlags;
    Core::Array<Math::Vec4> clearColors;
    float clearDepth;
    uint32 clearStencil;
    Math::Vec4 rect;
    int samples;
    bool isWindowTarget;
};

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetClearColor(const uint8 texture, const Math::Vec4& color)
{
    this->clearFlags = this->clearFlags | ClearFlags::Color;
    this->clearColors[texture] = color;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetClearDepth(const uint32 depth)
{
    this->clearFlags = this->clearFlags | ClearFlags::Depth;
    this->clearDepth = depth;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetClearStencil(const uint32 stencil)
{
    this->clearFlags = this->clearFlags | ClearFlags::Stencil;
    this->clearStencil = stencil;
}

//------------------------------------------------------------------------------
/**
*/
inline void
RenderTarget::SetViewport(uint32 left, uint32 top, uint32 width, uint32 height)
{
    this->rect = Math::Vec4(left, top, width, height);
}

}} // namespace JARVIS::Render