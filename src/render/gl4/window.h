#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::Window
	
    Implements a window using GLFW and assumes a GL 4+ context gets created.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "display/window.h"

struct GLFWwindow;
namespace JARVIS {
namespace GL4
{
class Window : public Base::Window
{
    __ClassDecl(Window);
public:
    /// constructor
    Window();
    /// destructor
    virtual ~Window();
    
    /// open window
    bool Open();
    /// close window
    void Close();
    
    /// make this window current for GL context
    void MakeCurrent();
    /// swap buffers at end of frame
    void SwapBuffers();
    
    /// updates all windows including events and such
    void Update();
    
private:

    GLFWwindow* window;

	/// static key press callback
	static void StaticKeyPressCallback(GLFWwindow* win, int32 key, int32 scancode, int32 action, int32 mods);
	/// static mouse press callback
	static void StaticMousePressCallback(GLFWwindow* win, int32 button, int32 action, int32 mods);
	/// static mouse move callback
	static void StaticMouseMoveCallback(GLFWwindow* win, float64 x, float64 y);
	/// static mouse enter/leave callback
	static void StaticMouseEnterLeaveCallback(GLFWwindow* win, int32 mode);
	/// static mouse scroll callback
	static void StaticMouseScrollCallback(GLFWwindow* win, float64 x, float64 y);
    /// static function which sets the closed flag of the window
    static void StaticWindowCloseCallback(GLFWwindow* win);
};

}} // namespace JARVIS::GL4