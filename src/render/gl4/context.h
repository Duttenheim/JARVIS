#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::Context
	
    Implements an OpenGL4 context which executes the OpenGL rendering pipeline.
    
    In OpenGL, this is the GLFW window handle.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "display/context.h"
struct GLFWwindow;
namespace JARVIS {
namespace GL4
{
class Context : public Base::Context
{
    __ClassDecl(Context);
public:
    /// constructor
    Context(GLFWwindow* window);
    /// destructor
    virtual ~Context();
    
    /// setup the context
    bool Setup();
    /// discard the context
    void Discard();
    
    /// make this context the current one
    void MakeCurrent();
    
    /// bind vertex buffers to be used
    void BindVertexBuffers(const InitList<Ptr<Render::VertexBuffer>>& vbos);
    /// bind index buffer to be used
    void BindIndexBuffer(const Ptr<Render::IndexBuffer>& ibo);
    /// bind render state to be used
    void BindRenderState(const Ptr<Render::RenderState>& renderState);
    /// bind render target to be used
    void BindRenderTarget(const Ptr<Render::RenderTarget>& renderTarget);
    
    /// draw using currently bound state
    void Draw();
    /// draw instanced
    void Draw(uint32 numInstances);
    
private:
    GLFWwindow* window;
};

}} // namespace JARVIS::GL4