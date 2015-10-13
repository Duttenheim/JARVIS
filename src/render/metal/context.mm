//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::Context
 	(C) 2015 See the LICENSE file.
*/
#include "context.h"
#include "types.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
Context::Context() :
    encoder(nullptr)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Context::~Context()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Hmmm, always selects default library, we might want to load that from file...
    
    Otherwise sets up the stuff necessary for a context, which allows for multiple contexts
    to be created if need be.
*/
bool
Context::Setup()
{
    Base::Context::Setup();
    this->device = MTLCreateSystemDefaultDevice();
    this->library = [this->device newDefaultLibrary];
    this->cmdQueue = [this->device newCommandQueue];
    this->cmdBuffer = [this->cmdQueue commandBuffer];
    this->MakeCurrent();
    return true;
}

//------------------------------------------------------------------------------
/**
*/
void
Context::Discard()
{
    Base::Context::Discard();
    [this->device release];
}

//------------------------------------------------------------------------------
/**
*/
void
Context::BindVertexBuffers(const InitList<Ptr<Render::VertexBuffer>>& vbos)
{
    j_assert(this->encoder != nullptr);
    Base::Context::BindVertexBuffers(Core::Forward(vbos));
    
    int32 i;
    for (i = 0; i < this->vbos.Size(); i++)
    {
        [this->encoder setVertexBuffer:this->vbos[i]->buffer offset:0 atIndex:i];
    }
}

//------------------------------------------------------------------------------
/**
*/
void
Context::BindIndexBuffer(const Ptr<Render::IndexBuffer>& ibo)
{
    j_assert(this->encoder != nullptr);
    Base::Context::BindIndexBuffer(Core::Forward(ibo));
}

//------------------------------------------------------------------------------
/**
*/
void
Context::BindPipelineState(const Ptr<Render::PipelineState>& pipelineState)
{
    Base::Context::BindPipelineState(Core::Forward(pipelineState));
    this->encoder = [this->cmdBuffer renderCommandEncoderWithDescriptor:pipelineState->rt->pass];
    [this->encoder setRenderPipelineState:pipelineState->renderPipeline];
    [this->encoder setViewport:*pipelineState->rt->viewport];
}

//------------------------------------------------------------------------------
/**
*/
void
Context::UnbindPipelineState()
{
    Base::Context::UnbindPipelineState();
    
    // end encoding and deref encoder (might not work as expected xD)
    [this->encoder endEncoding];
    this->encoder = nullptr;
}

//------------------------------------------------------------------------------
/**
    Hmmm, perhaps make this incremental somehow...
*/
void
Context::BindRenderState(const Ptr<Render::RenderState>& renderState)
{
    j_assert(this->encoder != nullptr);
    Base::Context::BindRenderState(Core::Forward(renderState));
    [this->encoder setCullMode:renderState->mtlCullMode];
    [this->encoder setDepthClipMode:renderState->mtlDepthClipMode];
    [this->encoder setFrontFacingWinding:renderState->mtlWinding];
    [this->encoder setScissorRect:renderState->mtlScissorRect];
    const auto stencilRef = renderState->stencilRef;
    [this->encoder setStencilFrontReferenceValue:stencilRef.frontRef backReferenceValue:stencilRef.backRef];
    [this->encoder setTriangleFillMode:renderState->mtlFillMode];
    const auto depthBias = renderState->depthBias;
    [this->encoder setDepthBias:depthBias.bias slopeScale:depthBias.slopeScale clamp:depthBias.clamp];
    [this->encoder setDepthStencilState:Base::Context::renderState->mtlDepthStencilState];
}

//------------------------------------------------------------------------------
/**
*/
void
Context::Draw()
{
    j_assert(this->encoder != nullptr);
    Base::Context::Draw();
    if (this->ibo != nullptr)
    {
        [this->encoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:this->primitive.indexCount indexType:this->ibo->indexType == IndexBuffer::IndexType::UShort ? MTLIndexTypeUInt16 : MTLIndexTypeUInt32 indexBuffer:this->ibo->buffer indexBufferOffset:this->primitive.baseIndex];
    }
    else
    {
        [this->encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:this->primitive.baseVertex vertexCount:this->primitive.vertexCount];
    }
    
}

//------------------------------------------------------------------------------
/**
*/
void
Context::Draw(uint32 numInstances)
{
    j_assert(this->encoder != nullptr);
    Base::Context::Draw(numInstances);
    if (this->ibo != nullptr)
    {
        [this->encoder drawIndexedPrimitives:Types::PrimitiveTopologyFlag(this->primitive.topo) indexCount:this->primitive.indexCount indexType:this->ibo->indexType == IndexBuffer::IndexType::UShort ? MTLIndexTypeUInt16 : MTLIndexTypeUInt32 indexBuffer:this->ibo->buffer indexBufferOffset:this->primitive.baseIndex instanceCount:numInstances];
    }
    else
    {
        [this->encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:this->primitive.baseVertex vertexCount:this->primitive.vertexCount instanceCount:numInstances];
    }
}

}} // namespace JARVIS::Metal
