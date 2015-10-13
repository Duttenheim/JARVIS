//------------------------------------------------------------------------------
/**
    @class JARVIS::WindowTest::WindowApp
 	(C) 2015 See the LICENSE file.
*/
#include "windowapp.h"
#include "threads/threading.h"
#include "context.h"

namespace JARVIS {
namespace WindowTest
{

//------------------------------------------------------------------------------
/**
*/
WindowApp::WindowApp()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
WindowApp::~WindowApp()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
WindowApp::Setup()
{
    this->window = Render::Window::Create();
    this->window->Open();
    auto func = Core::Functional::Lambda([this](int32, int32, int32) -> void
    {
        this->state = Application::Exiting;
    });
    this->window->SetMousePressFunction(func);
    
    // setup render target, this will be our window
    Ptr<Render::RenderTarget> rt = Render::RenderTarget::Create();
    rt->InitWithWindow(this->window);
    
    // setup pipeline state, which is shaders, render targets and blend states (which is empty, so we use default)
    Ptr<Render::PipelineState> pipelineState = Render::PipelineState::Create();
    Ptr<Render::Shader> vs = Render::Shader::Create(); vs->Load("vertex_shader");
    Ptr<Render::Shader> ps = Render::Shader::Create(); ps->Load("pixel_shader");
    pipelineState->InitRender({vs, ps}, rt, {});
    
    // setup render state
    Ptr<Render::RenderState> renderState = Render::RenderState::Create();
    
    // setup draw call data
    Ptr<Render::VertexBuffer> vbo0 = Render::VertexBuffer::Create();
    Render::Primitive prim;
    
    // update context and draw
    Ptr<Render::Context> context = Render::Context::Current;
    context->BindPipelineState(pipelineState);
    context->BindRenderState(renderState);
    context->BindVertexBuffers({vbo0});
    context->BindPrimitive(prim);
    context->Draw();
    context->UnbindPipelineState();
}

//------------------------------------------------------------------------------
/**
*/
void
WindowApp::OnFrame()
{
    this->window->Update();
    this->window->SwapBuffers();
}

//------------------------------------------------------------------------------
/**
*/
void
WindowApp::Exit()
{
    this->window->Close();
}

}} // namespace JARVIS::WindowTest
