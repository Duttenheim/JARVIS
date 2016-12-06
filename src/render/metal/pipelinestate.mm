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
PipelineState::InitRender(const Render::RenderShaderBundle& shaders, const Ptr<Render::RenderTarget>& rt, InitList<Render::BlendState> blendStates, const uint8 samples)
{
    Base::PipelineState::InitRender(shaders, rt, blendStates, samples);
    
    // setup descriptor
    MTLRenderPipelineDescriptor* desc = [[MTLRenderPipelineDescriptor alloc] init];
    desc.sampleCount = this->samples;
    desc.vertexFunction = this->vs->shader;
    desc.fragmentFunction = this->ps->shader;
    
    // assign attachments
    if (rt->isWindowTarget)
    {
        MTLRenderPipelineColorAttachmentDescriptor* colorAttachment = desc.colorAttachments[0];
        colorAttachment.pixelFormat = rt->view.colorPixelFormat;
        
        // set blend state if available
        if (this->blendStates.Size() > 0)
        {
            colorAttachment.blendingEnabled = this->blendStates[0].blendEnabled;
            colorAttachment.alphaBlendOperation = Types::BlendOpFlag(this->blendStates[0].alphaBlendOp);
            colorAttachment.rgbBlendOperation = Types::BlendOpFlag(this->blendStates[0].colorBlendOp);
            colorAttachment.sourceRGBBlendFactor = Types::BlendModeFlag(this->blendStates[0].srcColorBlendMode);
            colorAttachment.sourceAlphaBlendFactor = Types::BlendModeFlag(this->blendStates[0].srcAlphaBlendMode);
            colorAttachment.destinationRGBBlendFactor = Types::BlendModeFlag(this->blendStates[0].dstColorBlendMode);
            colorAttachment.destinationAlphaBlendFactor = Types::BlendModeFlag(this->blendStates[0].dstAlphaBlendMode);
        }
        
        desc.depthAttachmentPixelFormat = rt->view.depthStencilPixelFormat;
        desc.stencilAttachmentPixelFormat = Types::AsValidStencilFormat(rt->view.depthStencilPixelFormat);
    }
    else
    {
        for(uint32 i = 0; i < rt->textures.Size(); i++)
        {
            MTLRenderPipelineColorAttachmentDescriptor* attachment = desc.colorAttachments[i];
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
        
        //desc.depthAttachmentPixelFormat = rt->depthStencilTarget.depthStencilPixelFormat;
        //desc.stencilAttachmentPixelFormat = rt->depthStencilTarget.depthStencilPixelFormat;
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
PipelineState::InitCompute(const Render::ComputeShaderBundle& shader)
{
    Base::PipelineState::InitCompute(shader);
    
    // create pipeline
    NSError* err;
    this->computePipeline = [Context::Current->device newComputePipelineStateWithFunction:this->cs->shader error:&err];
    if (err != nil)
    {
        j_error([[err localizedDescription] cStringUsingEncoding:NSUTF8StringEncoding]);
    }
}

}} // namespace JARVIS::Metal