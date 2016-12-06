//------------------------------------------------------------------------------
/**
    @class JARVIS::WindowTest::WindowApp
 	(C) 2015 See the LICENSE file.
*/
#include "windowapp.h"
#include "threads/threading.h"
#include "math/mat4.h"
#include "context.h"



class Foobar
{
public:
    Foobar()
    {
        a = 0;
        b = 0;
    }
    Foobar(int i = 5, int f = 5)
    {
        a = i;
        b = f;
    }
private:
    int a, b;
};


namespace JARVIS {
namespace WindowTest
{

//------------------------------------------------------------------------------
/**
*/
WindowApp::WindowApp() :
    rot(0.0f)
{
    // empty
    
    Foobar foo;
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
WindowApp::OnSetup()
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
    
    // setup uniform buffer
    this->ubo = Render::UniformBuffer::Create();
    this->ubo->InitWithLayout({
        {"View", 64},
        {"Transform", 64}
        });
    this->member = this->ubo->GetMember("Transform");

    const Render::UniformBuffer::UniformMember view = this->ubo->GetMember("View");
    Math::Mat4 persp= Math::Mat4::Perspective(this->window->width, this->window->height, 0.001f, FLT_MAX, 0.5f, 1.0f);
    this->ubo->Update(view, (void*)persp.Get(), 64);

    
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
    this->renderState->depthCompare = Render::CompareMode::Always;
    this->renderState->depthMode = Render::DepthMode::Clamp;
    this->renderState->cullMode = Render::CullMode::None;
    this->renderState->scissorRect = Math::Vec4(0, 0, this->window->width, this->window->height);
    this->renderState->Commit();
    
    // setup draw data
    this->vbo = Render::VertexBuffer::Create();
    float vertices[] = {
        0, 0.5, 0,
        0.5, 0, 0,
        -0.5, -0, 0};
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
    context->NewFrame();
    context->BindPipelineState(this->pipeline);
    context->BindRenderState(this->renderState);
    context->BindVertexBuffers({this->vbo});
    context->BindPrimitive(this->prim);
    
    Math::Mat4 matrix = Math::Mat4::Translation(0, 0, 1.0f);
    matrix = Math::Mat4::Multiply(Math::Mat4::RotationY(rot), matrix);
    rot += 0.01f;
    this->ubo->Update(this->member, (void*)matrix.Get(), 64);
    context->BindUniformBuffer(this->ubo, Render::Context::Vertex, 0, 1);
    
    context->Draw();
    context->UnbindPipelineState();
    this->window->SwapBuffers();
}

//------------------------------------------------------------------------------
/**
*/
void
WindowApp::OnExit()
{
    this->window->Close();
}

}} // namespace JARVIS::WindowTest
