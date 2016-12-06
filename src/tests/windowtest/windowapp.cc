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
    this->rt = Render::RenderTarget::Create();
    this->rt->InitWithWindow(this->window);
    this->rt->SetClearColor(0, Math::Vec4(0, 0, 1, 0));
    
    // setup pipeline state, which is shaders, render targets and blend states (which is empty, so we use default)
    this->pipeline = Render::PipelineState::Create();
    Render::ShaderPtr vs = Render::Shader::Create(); vs->Load("basic_vertex");
    Render::ShaderPtr ps = Render::Shader::Create(); ps->Load("basic_fragment");
    Render::BlendState blend;
    blend.blendEnabled = true;
    blend.srcColorBlendMode = Render::BlendState::BlendMode::SourceAlpha;
    blend.dstColorBlendMode = Render::BlendState::BlendMode::OneMinusSourceAlpha;
    this->pipeline->InitRender(Render::RenderShaderBundle{vs, nullptr, nullptr, nullptr, ps}, rt, {blend}, 8);
    
    // setup render state, and commit it with default settings
    this->renderState = Render::RenderState::Create();
    this->renderState->scissorRect = Math::Vec4(0, 0, this->window->width, this->window->height);
    this->renderState->Commit();
    
    // setup draw data
    this->vbo = Render::VertexBuffer::Create();
    float vertices[] = {0, 1, 0, 1, -1, 0, -1, -1, 0};
    this->vbo->InitImmutable({Render::VertexBuffer::VertexComponent{4, 0, Render::ComponentType::Float}}, sizeof(vertices), (byte*)vertices);
    this->prim.vertexCount = 3;
}

//------------------------------------------------------------------------------
/**
*/
void
WindowApp::OnFrame()
{
    this->window->Update();
    // update context and draw
    Render::ContextPtr context = Render::Context::Current;
    context->BindPipelineState(this->pipeline);
    context->BindRenderState(this->renderState);
    context->BindVertexBuffers({this->vbo});
    context->BindPrimitive(this->prim);
    context->Draw();
    context->UnbindPipelineState();
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
