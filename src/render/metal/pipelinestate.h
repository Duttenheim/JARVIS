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
#include "types.h"
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
    void InitRender(const Render::RenderShaderBundle& shaders, const Ptr<Render::RenderTarget>& rt, InitList<Render::BlendState> blendStates, const uint8 samples = 1);
    /// setup from compute pipeline
    void InitCompute(const Render::ComputeShaderBundle& shader);
    
private:
    friend class Metal::Context;
    OBJC_ID_POINTER(MTLRenderPipelineState) renderPipeline;
    OBJC_ID_POINTER(MTLComputePipelineState) computePipeline;
};

}} // namespace JARVIS::Metal