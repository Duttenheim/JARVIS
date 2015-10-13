#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::PipelineState
	
    Implements a Metal pipeline state.
    Even though Metal doesn't support geometry based shaders, 
    they are still present in the event they will be at some later point.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "resources/pipelinestate.h"
namespace JARVIS {
namespace Metal
{
class Context;
class PipelineState : public Base::PipelineState
{
public:
    /// constructor
    PipelineState();
    /// destructor
    virtual ~PipelineState();
    
    /// setup from graphics pipeline
    /// 1: vertex, 2: geometry, 3: hull, 4: domain, 5: fragment
    void InitRender(const InitList<Ptr<Render::Shader>>& shaders, const Ptr<Render::RenderTarget>& rt, const InitList<Render::BlendState>& blendStates);
    /// setup from compute pipeline
    void InitCompute(const Ptr<Render::Shader>& shader);
    
private:
    friend class Metal::Context;
    OBJC_ID_POINTER(MTLRenderPipelineState) renderPipeline;
    OBJC_ID_POINTER(MTLComputePipelineState) computePipeline;
};

}} // namespace JARVIS::Metal