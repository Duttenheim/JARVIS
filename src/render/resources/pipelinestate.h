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
    void InitRender(const InitList<Ptr<Render::Shader>>& shaders, const Ptr<Render::RenderTarget>& rt, const InitList<Render::BlendState>& blendStates);
    /// setup from compute pipeline
    void InitCompute(const Ptr<Render::Shader>& shader);
    
protected:
    Ptr<Render::Shader> vs;
    Ptr<Render::Shader> gs;
    Ptr<Render::Shader> hs;
    Ptr<Render::Shader> ds;
    Ptr<Render::Shader> fs;
    Ptr<Render::Shader> cs;
    Ptr<Render::RenderTarget> rt;
    Core::Array<Render::BlendState> blendStates;
};


//------------------------------------------------------------------------------
/**
*/
inline void
PipelineState::InitRender(const InitList<Ptr<Render::Shader>>& shaders, const Ptr<Render::RenderTarget>& rt, const InitList<Render::BlendState>& blendStates)
{
    this->vs = nullptr;
    this->gs = nullptr;
    this->hs = nullptr;
    this->ds = nullptr;
    this->fs = nullptr;
    this->cs = nullptr;
    this->rt = rt;
    uint32 i;
    for (i = 0; i < shaders.size(); i++)
    {
        switch (i)
        {
            case 0: this->vs = *(shaders.begin() + i);
                break;
            case 1: this->gs = *(shaders.begin() + i);
                break;
            case 2: this->hs = *(shaders.begin() + i);
                break;
            case 3: this->ds = *(shaders.begin() + i);
                break;
            case 4: this->fs = *(shaders.begin() + i);
                break;
            default:
                return;
        }
    }
    this->blendStates = blendStates;
}

//------------------------------------------------------------------------------
/**
*/
inline void
PipelineState::InitCompute(const Ptr<Render::Shader>& shader)
{
    this->vs = nullptr;
    this->gs = nullptr;
    this->hs = nullptr;
    this->ds = nullptr;
    this->fs = nullptr;
    this->cs = shader;
    this->rt = nullptr;
}

}} // namespace JARVIS::Base