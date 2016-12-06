#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Base::RenderState
	
    A render state encapsules a complete rendering state, complete with setting:
    
    Blend settings, stencil settings, depth settings as well as polygon and rasterizer settings.
 
    One must call Commit on the render state to apply the current changes to the actual render state object.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "renderstatetypes.h"
#include "math/vec4.h"
namespace JARVIS {
namespace Base
{
class RenderState : public Core::Ref
{
    __ClassDecl(RenderState);
public:

    /// constructor
    RenderState();
    /// destructor
    virtual ~RenderState();
    
    /// end change region, all changes done from the last begin will take place
    void Commit();

    Render::CullMode cullMode;
    Render::Winding winding;
    Render::DepthMode depthMode;
    Render::FillMode fillMode;
    
    struct
    {
        Render::StencilOp sfail;
        Render::StencilOp dfail;
        Render::StencilOp dspass;
        Render::CompareMode compareMode;
        uint32 readMask, writeMask;
    } backFaceStencil, frontFaceStencil;
    struct
    {
        uint32 frontRef, backRef;
    } stencilRef;
    
    struct
    {
        float32 bias, slopeScale, clamp;
    } depthBias;
    bool depthWrite;
    Render::CompareMode depthCompare;
    Math::Vec4 scissorRect;
};

}} // namespace JARVIS::Base