//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::Context
 	(C) 2015 See the LICENSE file.
*/
#include "context.h"
#include "types.h"
#include "window.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
Context::Context() :
    device(nil),
    library(nil),
    cmdQueue(nil),
    cmdBuffer(nil),
    encoder(nil)
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
    this->library = [this->device newLibraryWithFile:METAL_DEFAULT_LIB error:nil];
    this->cmdQueue = [this->device newCommandQueue];
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
Context::BindVertexBuffers(InitList<Ptr<Render::VertexBuffer>> vbos)
{
    if (this->encoder == nil) return;
    Base::Context::BindVertexBuffers(Fw(vbos));
    
    int32 i;
    for (i = 0; i < this->vbos.Size(); i++)
    {
        j_assert(this->vbos[i]->buffer != nullptr);
        [this->encoder setVertexBuffer:this->vbos[i]->buffer offset:0 atIndex:i];
    }
}

//------------------------------------------------------------------------------
/**
*/
void
Context::BindIndexBuffer(const Ptr<Render::IndexBuffer>& ibo)
{
    if (this->encoder == nil) return;
    Base::Context::BindIndexBuffer(Fw(ibo));
}

//------------------------------------------------------------------------------
/**
*/
void
Context::BindPipelineState(const Ptr<Render::PipelineState>& pipelineState)
{
    Base::Context::BindPipelineState(Fw(pipelineState));
    if (this->encoder != nil)
    {
        [this->encoder endEncoding];
        this->encoder = nil;
    }
    if (this->cmdBuffer == nil) return;
    this->encoder = [this->cmdBuffer renderCommandEncoderWithDescriptor:pipelineState->rt->GetPass()];
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
}

//------------------------------------------------------------------------------
/**
    Hmmm, perhaps make this incremental somehow...
*/
void
Context::BindRenderState(const Ptr<Render::RenderState>& renderState)
{
    if (this->encoder == nil) return;
    Base::Context::BindRenderState(Fw(renderState));
    
    MTLCullMode cullMode;
    // set cull mode
    switch (renderState->cullMode)
    {
        case Render::CullMode::Front:   cullMode = MTLCullModeFront;
        break;
        case Render::CullMode::Back:    cullMode = MTLCullModeBack;
        break;
        case Render::CullMode::None:    cullMode = MTLCullModeNone;
        break;
    }
    
    MTLWinding winding;
    // set winding mode
    switch (renderState->winding)
    {
        case Render::Winding::Clockwise:            winding = MTLWindingClockwise;
        break;
        case Render::Winding::CounterClockwise:     winding = MTLWindingCounterClockwise;
        break;
    }
    
    MTLDepthClipMode clipMode;
    // set depth mode
    switch (renderState->depthMode)
    {
        case Render::DepthMode::Clamp:          clipMode = MTLDepthClipModeClamp;
        break;
        case Render::DepthMode::Clip:           clipMode = MTLDepthClipModeClip;
        break;
    }
    
    MTLTriangleFillMode triangleFillMode;
    // set fill mode
    switch (renderState->fillMode)
    {
        case Render::FillMode::Fill:            triangleFillMode = MTLTriangleFillModeFill;
        break;
        case Render::FillMode::Lines:           triangleFillMode = MTLTriangleFillModeLines;
        break;
    }
    
    [this->encoder setCullMode:cullMode];
    [this->encoder setDepthClipMode:clipMode];
    [this->encoder setFrontFacingWinding:winding];
    [this->encoder setTriangleFillMode:triangleFillMode];
    [this->encoder setScissorRect:*renderState->mtlScissorRect];
    const auto stencilRef = renderState->stencilRef;
    [this->encoder setStencilFrontReferenceValue:stencilRef.frontRef backReferenceValue:stencilRef.backRef];
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
    if (this->encoder == nil) return;
    Base::Context::Draw();
    if (this->ibo != nullptr)
    {
        [this->encoder drawIndexedPrimitives:MTLPrimitiveTypeTriangle indexCount:this->primitive.indexCount indexType:this->ibo->indexType == IndexBuffer::IndexType::UShort ? MTLIndexTypeUInt16 : MTLIndexTypeUInt32 indexBuffer:this->ibo->buffer indexBufferOffset:this->primitive.baseIndex instanceCount:1];
    }
    else
    {
        [this->encoder drawPrimitives:MTLPrimitiveTypeTriangle vertexStart:this->primitive.baseVertex vertexCount:this->primitive.vertexCount instanceCount:1];
    }
}

//------------------------------------------------------------------------------
/**
*/
void
Context::Draw(uint32 numInstances)
{
    if (this->encoder == nil) return;
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

//------------------------------------------------------------------------------
/**
*/
void
Context::NewFrame()
{
    this->cmdBuffer = nil;
    this->cmdBuffer = [this->cmdQueue commandBuffer];
}

//------------------------------------------------------------------------------
/**
*/
void
Context::Present(const Ptr<Metal::Window>& window)
{
    if (this->cmdBuffer != nil && this->encoder != nil)
    {
        [this->encoder endEncoding];
        [this->cmdBuffer presentDrawable:window->view.currentDrawable];
        [this->cmdBuffer commit];
    }
    this->encoder = nil;
}
}} // namespace JARVIS::Metal
