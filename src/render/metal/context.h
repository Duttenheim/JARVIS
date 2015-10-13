#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::Context
	
    Implements a metal context.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "display/context.h"
namespace JARVIS {
namespace Metal
{
class Window;
class Context : public Base::Context
{
    __ClassDecl(Context);
public:
    /// constructor
    Context();
    /// destructor
    virtual ~Context();
    
    /// setup context
    bool Setup();
    /// discard
    void Discard();
    
    /// bind render target to be used
    void BindPipelineState(const Ptr<Render::PipelineState>& renderTarget);
    /// unbind pipeline, which denotes the end of a frame
    void UnbindPipelineState();
    /// bind vertex buffers to be used
    void BindVertexBuffers(const InitList<Ptr<Render::VertexBuffer>>& vbos);
    /// bind index buffer to be used
    void BindIndexBuffer(const Ptr<Render::IndexBuffer>& ibo);
    /// bind render state to be used
    void BindRenderState(const Ptr<Render::RenderState>& renderState);
    
    /// draw using currently bound state
    void Draw();
    /// draw instanced
    void Draw(uint32 numInstances);
    
private:
    friend class Metal::Window;
    friend class Metal::VertexBuffer;
    friend class Metal::IndexBuffer;
    friend class Metal::RenderState;
    friend class Metal::PipelineState;
    friend class Metal::Shader;
    OBJC_ID_POINTER(MTLDevice) device;
    OBJC_ID_POINTER(MTLLibrary) library;
    OBJC_ID_POINTER(MTLCommandQueue) cmdQueue;
    OBJC_ID_POINTER(MTLCommandBuffer) cmdBuffer;
    OBJC_ID_POINTER(MTLRenderCommandEncoder) encoder;
};

}} // namespace JARVIS::Metal