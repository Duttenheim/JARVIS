//------------------------------------------------------------------------------
/**
    @class JARVIS::GL4::Context
 	(C) 2015 See the LICENSE file.
*/
#include "context.h"
#include "glfw3.h"
namespace JARVIS {
namespace GL4
{
    
//------------------------------------------------------------------------------
/**
*/
Context::Context(GLFWwindow* window) :
    window(window)
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
*/
bool
Context::Setup()
{
    // step 1, make context current
    this->MakeCurrent();
    
    // setup glew
    GLenum res = glewInit();
    assert(res == GLEW_OK);
    if (!(GLEW_VERSION_4_1))
    {
        printf("[WARNING]: OpenGL 4.1+ is not supported on this hardware!\n");
        printf("Current GL version: %s", glewGetString(GLEW_VERSION));
        return false;
    }
    
#if OPENGL_VERSION_MAX >= 43
    // setup debug callback
    glEnable(GL_DEBUG_OUTPUT);
    glEnable(GL_DEBUG_OUTPUT_SYNCHRONOUS);
    glDebugMessageCallback(GLDebugCallback, NULL);
    GLuint unusedIds;
    glDebugMessageControl(GL_DONT_CARE, GL_DONT_CARE, GL_DONT_CARE, 0, &unusedIds, true);
#endif

    // setup stuff
    glEnable(GL_FRAMEBUFFER_SRGB);
    glEnable(GL_LINE_SMOOTH);
    glEnable(GL_POLYGON_SMOOTH);
    glEnable(GL_MULTISAMPLE);
    glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
    glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
    return true;
}

//------------------------------------------------------------------------------
/**
*/
void
Context::Discard()
{
    this->window = nullptr;
}

//------------------------------------------------------------------------------
/**
*/
void
Context::MakeCurrent()
{
    Base::Context::MakeCurrent();
    glfwMakeContextCurrent(this->window);
}

//------------------------------------------------------------------------------
/**
*/
void
Context::BindVertexBuffers(const InitList<Ptr<Render::VertexBuffer>>& vbos)
{
    Base::Context::BindVertexBuffers(vbos);
    int32 i;
    uint32 lastComponentIndex = 0;
    for (i = 0; i < this->vbos.Size(); i++)
    {
        this->vbos[i]->Bind(lastComponentIndex);
    }
}

//------------------------------------------------------------------------------
/**
*/
void
Context::BindIndexBuffer(const Ptr<Render::IndexBuffer>& ibo)
{
    Base::Context::BindIndexBuffer(ibo);
}

//------------------------------------------------------------------------------
/**
*/
void
Context::BindRenderState(const Ptr<Render::RenderState>& renderState)
{
    Base::Context::BindRenderState(renderState);
}

//------------------------------------------------------------------------------
/**
*/
void
Context::BindRenderTarget(const Ptr<Render::RenderTarget>& renderTarget)
{
    Base::Context::BindRenderTarget(renderTarget);
}

}} // namespace JARVIS::GL4
