//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::PipelineState
 	(C) 2015 See the LICENSE file.
*/
#include "pipelinestate.h"
#include "types.h"
#include "../texture.h"
#include "../context.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
PipelineState::PipelineState() :
    renderPipeline(nullptr),
    computePipeline(nullptr)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
PipelineState::~PipelineState()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
PipelineState::InitRender(const InitList<Ptr<Render::Shader>>& shaders, const Ptr<Render::RenderTarget>& rt, const InitList<Render::BlendState>& blendStates)
{
    Base::PipelineState::InitRender(Core::Forward(shaders), Core::Forward(rt), Core::Forward(blendStates));
    
    // setup descriptor
    MTLRenderPipelineDescriptor* desc = [[MTLRenderPipelineDescriptor alloc] init];
    desc.vertexFunction = this->vs->shader;
    desc.vertexFunction = this->fs->shader;
    
    // assign attachments
    int32 i;
    for(i = 0; i < rt->textures.Size(); i++)
    {
        MTLRenderPipelineColorAttachmentDescriptor* attachment = [desc.colorAttachments objectAtIndexedSubscript:i];
        attachment.pixelFormat = (MTLPixelFormat)Types::PixelFormatFlag(rt->textures[i]->pixelFormat);
        
        // setup blend state if we have a descriptor for it
        if (this->blendStates.Size() > i)
        {
            attachment.blendingEnabled = this->blendStates[i].blendEnabled;
            attachment.alphaBlendOperation = Types::BlendOpFlag(this->blendStates[i].alphaBlendOp);
            attachment.rgbBlendOperation = Types::BlendOpFlag(this->blendStates[i].colorBlendOp);
            attachment.sourceRGBBlendFactor = Types::BlendModeFlag(this->blendStates[i].srcColorBlendMode);
            attachment.sourceAlphaBlendFactor = Types::BlendModeFlag(this->blendStates[i].srcAlphaBlendMode);
            attachment.destinationRGBBlendFactor = Types::BlendModeFlag(this->blendStates[i].dstColorBlendMode);
            attachment.destinationAlphaBlendFactor = Types::BlendModeFlag(this->blendStates[i].dstAlphaBlendMode);
        }
        else
        {
            // create default placeholder state and assign, this avoids random attachment behaviour
            const Render::BlendState placeholder(nullptr);
            attachment.blendingEnabled = placeholder.blendEnabled;
            attachment.alphaBlendOperation = Types::BlendOpFlag(placeholder.alphaBlendOp);
            attachment.rgbBlendOperation = Types::BlendOpFlag(placeholder.colorBlendOp);
            attachment.sourceRGBBlendFactor = Types::BlendModeFlag(placeholder.srcColorBlendMode);
            attachment.sourceAlphaBlendFactor = Types::BlendModeFlag(placeholder.srcAlphaBlendMode);
            attachment.destinationRGBBlendFactor = Types::BlendModeFlag(placeholder.dstColorBlendMode);
            attachment.destinationAlphaBlendFactor = Types::BlendModeFlag(placeholder.dstAlphaBlendMode);
        }
    }
    
    // create pipeline
    NSError* err;
    this->renderPipeline = [Context::Current->device newRenderPipelineStateWithDescriptor:desc error:&err];
    if (err != nil)
    {
        j_error([[err localizedDescription] cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}

//------------------------------------------------------------------------------
/**
*/
void
PipelineState::InitCompute(const Ptr<Render::Shader>& shader)
{
    Base::PipelineState::InitCompute(Core::Forward(shader));
    
    // create pipeline
    NSError* err;
    this->computePipeline = [Context::Current->device newComputePipelineStateWithFunction:shader->shader error:&err];
    if (err != nil)
    {
        j_error([[err localizedDescription] cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}

}} // namespace JARVIS::Metal