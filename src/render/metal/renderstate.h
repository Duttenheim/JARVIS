#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::RenderState
	
    Metal implementation of a render state (or pipeline object)
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "resources/renderstate.h"
namespace JARVIS {
namespace Metal
{
class Context;
class RenderState : public Base::RenderState
{
    __ClassDecl(RenderState);
public:
    /// constructor
    RenderState();
    /// destructor
    virtual ~RenderState();
    
    /// update implementation types when we end the change
    void Commit();

    /// set cull mode
    void SetCulling(const Render::CullMode cull);
    /// set winding mode
    void SetWinding(const Render::Winding winding);
    /// set depth mode
    void SetDepthMode(const Render::DepthMode depthMode);
    /// set depth bias
    void SetDepthBias(const float32 bias, const float32 slopeScale, const float32 clamp);
    /// set fill mode
    void SetFillMode(const Render::FillMode fillMode);
    /// set stencil references
    void SetStencilRef(const uint32 frontRef, const uint32 backRef);
    /// set scissor rect
    void SetScissorRect(const uint32 left, const uint32 top, const uint32 width, const uint32 height);
    
private:
    friend class Context;
    OBJC_ID_POINTER(MTLDepthStencilState) mtlDepthStencilState;
    OBJC_ENUM_TYPE(MTLCullMode) mtlCullMode;
    OBJC_ENUM_TYPE(MTLDepthClipMode) mtlDepthClipMode;
    OBJC_ENUM_TYPE(MTLScissorRect) mtlScissorRect;
    OBJC_ENUM_TYPE(MTLBlendFactor) mtlBlendFactor;
    OBJC_ENUM_TYPE(MTLBlendOperation) mtlBlendOp;
    OBJC_ENUM_TYPE(MTLStencilOperation) mtlStencilOp;
    OBJC_ENUM_TYPE(MTLWinding) mtlWinding;
    OBJC_ENUM_TYPE(MTLTriangleFillMode) mtlFillMode;
};

}} // namespace JARVIS::Metal