//------------------------------------------------------------------------------
/**
    @class JARVIS::GL4::Window
 	(C) 2015 See the LICENSE file.
*/
#include "window.h"
#include "glfw3.h"
#include "context.h"
#include "../context.h"
#include "../rendertarget.h"
#include "../window.h"
namespace JARVIS {
namespace GL4
{
 
#if OPENGL_VERSION_MAX >= 43
//------------------------------------------------------------------------------
/**
*/
static void GLAPIENTRY
GLDebugCallback(GLenum source, GLenum type, GLuint id, GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
	std::string msg("[OPENGL DEBUG MESSAGE] ");

	// print error severity
	switch (severity)
	{
	case GL_DEBUG_SEVERITY_LOW:
		msg.append("<Low severity> ");
		break;
	case GL_DEBUG_SEVERITY_MEDIUM:
		msg.append("<Medium severity> ");
		break;
	case GL_DEBUG_SEVERITY_HIGH:
		msg.append("<High severity> ");
		break;
	}

	// append message to output
	msg.append(message);

	// print message
	switch (type)
	{
	case GL_DEBUG_TYPE_ERROR:
	case GL_DEBUG_TYPE_UNDEFINED_BEHAVIOR:
		printf("Error: %s\n", msg.c_str());
		break;
	case GL_DEBUG_TYPE_PERFORMANCE:
		printf("Performance issue: %s\n", msg.c_str());
		break;
	default:		// Portability, Deprecated, Other
		break;
	}
}
#endif
   

//------------------------------------------------------------------------------
/**
*/
Window::Window() :
    Base::Window(),
    window(nullptr)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Window::~Window()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
bool
Window::Open()
{
    if (GlobalWindowCounter == 0)
    {
        if (!glfwInit()) return false;
    }
    
    // setup window
	glfwWindowHint(GLFW_OPENGL_DEBUG_CONTEXT, GL_TRUE);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

#if __APPLE__
    // just request the highest context suited for OS X
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
#endif

	glfwWindowHint(GLFW_RED_BITS, 8);
	glfwWindowHint(GLFW_GREEN_BITS, 8);
	glfwWindowHint(GLFW_BLUE_BITS, 8);
	glfwWindowHint(GLFW_SRGB_CAPABLE, GL_TRUE);
	glfwWindowHint(GLFW_SAMPLES, 8);
    
    // create window and make current directly
    this->window = glfwCreateWindow(this->width, this->height, this->title.CharPtr(), nullptr, nullptr);
    
    if (nullptr != this->window && Window::GlobalWindowCounter == 0)
    {
        // explicitly setup a GL4 context using this window as it's context source
        this->context = GL4::Context::Create(this->window);
        this->context->Setup();
        
        // setup default render target
        this->renderTarget = GL4::RenderTarget::Create();
        this->renderTarget->Setup(this);
        
        // setup callbacks
        glfwSetWindowUserPointer(this->window, this);
        glfwSetKeyCallback(this->window, Window::StaticKeyPressCallback);
        glfwSetMouseButtonCallback(this->window, Window::StaticMousePressCallback);
        glfwSetCursorPosCallback(this->window, Window::StaticMouseMoveCallback);
        glfwSetCursorEnterCallback(this->window, Window::StaticMouseEnterLeaveCallback);
        glfwSetScrollCallback(this->window, Window::StaticMouseScrollCallback);
        glfwSetWindowCloseCallback(this->window, Window::StaticWindowCloseCallback);
        
        glDrawPixels(1, 1, GL_RGB, GL_UNSIGNED_BYTE, nullptr);
        
        // call base class
        Base::Window::Open();
    }
    
    return this->window != nullptr;

}

//------------------------------------------------------------------------------
/**
*/
void
Window::Close()
{
    j_assert(this->window != nullptr);
    j_assert(this->context != nullptr);
    
    // discard the context
    this->context->Discard();
    this->context = nullptr;
    
    // discard the window
    glfwDestroyWindow(this->window);
    this->window = nullptr;
    
    Base::Window::Close();
}

//------------------------------------------------------------------------------
/**
*/
void
Window::MakeCurrent()
{
    j_assert(this->window != nullptr);
    j_assert(this->context != nullptr);
    this->context->MakeCurrent();
}

//------------------------------------------------------------------------------
/**
*/
void
Window::SwapBuffers()
{
    j_assert(this->window != nullptr);
    glfwSwapBuffers(this->window);
    Base::Window::SwapBuffers();
}

//------------------------------------------------------------------------------
/**
*/
void
Window::Update()
{
    glfwPollEvents();
    Base::Window::Update();
}

//------------------------------------------------------------------------------
/**
*/
void
Window::StaticKeyPressCallback(GLFWwindow* win, int32 key, int32 scancode, int32 action, int32 mods)
{
	Window* window = (Window*)glfwGetWindowUserPointer(win);
	if (window->keyPressCallback != nullptr) window->keyPressCallback->Call(key, scancode, action, mods);
}

//------------------------------------------------------------------------------
/**
*/
void
Window::StaticMousePressCallback(GLFWwindow* win, int32 button, int32 action, int32 mods)
{
	Window* window = (Window*)glfwGetWindowUserPointer(win);
	if (window->mousePressCallback != nullptr) window->mousePressCallback->Call(button, action, mods);
}

//------------------------------------------------------------------------------
/**
*/
void
Window::StaticMouseMoveCallback(GLFWwindow* win, float64 x, float64 y)
{
	Window* window = (Window*)glfwGetWindowUserPointer(win);
	if (window->mouseMoveCallback != nullptr) window->mouseMoveCallback->Call(x, y);
}

//------------------------------------------------------------------------------
/**
*/
void
Window::StaticMouseEnterLeaveCallback(GLFWwindow* win, int32 mode)
{
	Window* window = (Window*)glfwGetWindowUserPointer(win);
	if (window->mouseLeaveEnterCallback != nullptr) window->mouseLeaveEnterCallback->Call(mode == 0);
}

//------------------------------------------------------------------------------
/**
*/
void
Window::StaticMouseScrollCallback(GLFWwindow* win, float64 x, float64 y)
{
	Window* window = (Window*)glfwGetWindowUserPointer(win);
	if (window->mouseScrollCallback != nullptr) window->mouseScrollCallback->Call(x, y);
}

//------------------------------------------------------------------------------
/**
*/
void
Window::StaticWindowCloseCallback(GLFWwindow* win)
{
	Window* window = (Window*)glfwGetWindowUserPointer(win);
    window->Close();
}

}}
