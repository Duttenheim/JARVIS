#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Base::Context
	
    Implements a context, which is the basis for all rendering commands.
    This object holds the current state
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "ref.h"
#include "util/array.h"
#include "util/tuple.h"
#include "resources/primitive.h"
#include "../vertexbuffer.h"
#include "../indexbuffer.h"
#include "../renderstate.h"
#include "../pipelinestate.h"
#include "../shader.h"
#include <utility>

namespace JARVIS {
namespace Render
{
class Context;
}}

namespace JARVIS {
namespace Base
{
class Context : public Core::Ref
{
    __ClassDecl(Context);
public:
    /// constructor
    Context();
    /// destructor
    virtual ~Context();
    
    /// setup the context
    bool Setup();
    /// discard the context
    void Discard();
    
    /// make this context the current one
    void MakeCurrent();
    
    /// request the load of a shader, and save it to dictionary
    Ptr<Render::Shader> LoadShader(const Core::String& name);
    
    /// bind pipeline state to be used, all other binds must happen after this is done
    void BindPipelineState(const Ptr<Render::PipelineState>& renderTarget);
    /// unbind pipeline, which denotes the end of a frame
    void UnbindPipelineState();
    /// bind vertex buffers to be used
    void BindVertexBuffers(const InitList<Ptr<Render::VertexBuffer>>& vbos);
    /// bind index buffer to be used
    void BindIndexBuffer(const Ptr<Render::IndexBuffer>& ibo);
    /// bind render state to be used
    void BindRenderState(const Ptr<Render::RenderState>& renderState);
    /// bind primitive to be used by draw
    void BindPrimitive(const Render::Primitive& prim);
    
    /// draw using currently bound state
    void Draw();
    /// draw instanced
    void Draw(uint32 numInstances);
    
    static Render::Context* Current;
protected:
    Render::Primitive primitive;
    Core::Array<Ptr<Render::VertexBuffer>> vbos;
    Ptr<Render::IndexBuffer> ibo;
    Ptr<Render::RenderState> renderState;
    Ptr<Render::PipelineState> pipelineState;
    Core::Map<uint32, Ptr<Render::Shader>> shaders;
};

//------------------------------------------------------------------------------
/**
*/
inline void
Context::BindPipelineState(const Ptr<Render::PipelineState>& pipelineState)
{
    this->pipelineState = pipelineState;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Context::UnbindPipelineState()
{
    this->pipelineState = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Context::BindVertexBuffers(const InitList<Ptr<Render::VertexBuffer>>& vbos)
{
    this->vbos = vbos;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Context::BindIndexBuffer(const Ptr<Render::IndexBuffer>& ibo)
{
    this->ibo = ibo;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Context::BindRenderState(const Ptr<Render::RenderState>& renderState)
{
    this->renderState = renderState;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Context::BindPrimitive(const Render::Primitive& prim)
{
    this->primitive = prim;
}

}} // namespace JARVIS::Base