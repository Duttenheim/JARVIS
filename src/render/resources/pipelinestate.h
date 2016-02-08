#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Base::PipelineState
	
    A pipeline state represents a state which holds the inputs and
    outputs from the rendering pipeline, such as vertex layouts in the back,
    and render targets in the front.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "../shader.h"
#include "../rendertarget.h"
#include "blendstate.h"
namespace JARVIS {
namespace Render
{

struct RenderShaderBundle
{
    Ptr<Render::Shader> vs;
    Ptr<Render::Shader> gs;
    Ptr<Render::Shader> hs;
    Ptr<Render::Shader> ds;
    Ptr<Render::Shader> ps;
};

struct ComputeShaderBundle
{
    Ptr<Render::Shader> cs;
};
    
class Shader;
class RenderTarget;
}}

namespace JARVIS {
namespace Base
{
class PipelineState : public Core::Ref
{
    __ClassDecl(PipelineState);
public:
    /// constructor
    PipelineState();
    /// destructor
    virtual ~PipelineState();
    
    /// setup from graphics pipeline, shaders are sent as an array corresponding to:
    /// 1: vertex, 2: geometry, 3: hull, 4: domain, 5: fragment
    void InitRender(const Render::RenderShaderBundle& shaders, const Ptr<Render::RenderTarget>& rt, InitList<Render::BlendState> blendStates, const uint8 samples = 1);
    /// setup from compute pipeline
    void InitCompute(const Render::ComputeShaderBundle& shader);
    
protected:
    Ptr<Render::Shader> vs;
    Ptr<Render::Shader> gs;
    Ptr<Render::Shader> hs;
    Ptr<Render::Shader> ds;
    Ptr<Render::Shader> ps;
    Ptr<Render::Shader> cs;
    Ptr<Render::RenderTarget> rt;
    uint8 samples;
    Core::Array<Render::BlendState> blendStates;
};


//------------------------------------------------------------------------------
/**
*/
inline void
PipelineState::InitRender(const Render::RenderShaderBundle& shaders, const Ptr<Render::RenderTarget>& rt, InitList<Render::BlendState> blendStates, const uint8 samples)
{
    this->vs = shaders.vs;
    this->gs = shaders.gs;
    this->hs = shaders.hs;
    this->ds = shaders.ds;
    this->ps = shaders.ps;
    this->cs = nullptr;
    this->rt = rt;
    this->samples = samples;
    this->blendStates = blendStates;
}

//------------------------------------------------------------------------------
/**
*/
inline void
PipelineState::InitCompute(const Render::ComputeShaderBundle& shader)
{
    this->vs = nullptr;
    this->gs = nullptr;
    this->hs = nullptr;
    this->ds = nullptr;
    this->ps = nullptr;
    this->cs = shader.cs;
    this->rt = nullptr;
}

}} // namespace JARVIS::Base