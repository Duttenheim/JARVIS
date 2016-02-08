//------------------------------------------------------------------------------
/**
    @class JARVIS::Base::RenderState
 	(C) 2015 See the LICENSE file.
*/
#include "renderstate.h"
namespace JARVIS {
namespace Base
{
    
//------------------------------------------------------------------------------
/**
*/
RenderState::RenderState() :
    cullMode(Render::CullMode::Back),
    winding(Render::Winding::Clockwise),
    depthMode(Render::DepthMode::Clip),
    fillMode(Render::FillMode::Fill),
    backFaceStencil({Render::StencilOp::Keep,Render::StencilOp::Keep,Render::StencilOp::Keep,Render::CompareMode::Always, 0xFF, 0xFF}),
    frontFaceStencil({Render::StencilOp::Keep,Render::StencilOp::Keep,Render::StencilOp::Keep,Render::CompareMode::Always, 0xFF, 0xFF}),
    stencilRef({0, 0}),
    depthWrite(true),
    depthCompare(Render::CompareMode::LessEqual),
    scissorRect(Math::Vec4(0))
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
RenderState::~RenderState()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
RenderState::Commit()
{
    // empty, override in subclass
}

}} // Base::RenderState
