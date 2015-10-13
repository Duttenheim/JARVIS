#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Display::Window
	
    Base class for windows. Doesn't actually open a window;
    that's done by the implementation.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "util/string.h"
#include "functional/function.h"
#include "../context.h"
#include "../rendertarget.h"

namespace JARVIS {
namespace Base
{
class Window : public Core::Ref
{
    __ClassDecl(Window);
public:
    /// constructor
    Window();
    /// destructor
    virtual ~Window();
    
    /// set window width
    void SetWidth(const uint32 width);
    /// set window height
    void SetHeight(const uint32 height);
    /// set window title
    void SetTitle(const Core::String& title);
    
    /// set key press function callback
	void SetKeyPressFunction(const Ptr<Core::Function<void(int32, int32, int32, int32)>>& func);
	/// set mouse press function callback
	void SetMousePressFunction(const Ptr<Core::Function<void(int32, int32, int32)>>& func);
	/// set mouse move function callback
	void SetMouseMoveFunction(const Ptr<Core::Function<void(float64, float64)>>& func);
	/// set mouse enter leave function callback
	void SetMouseEnterLeaveFunction(const Ptr<Core::Function<void(bool)>>& func);
	/// set mouse scroll function callback
	void SetMouseScrollFunction(const Ptr<Core::Function<void(float64, float64)>>& func);
    
    /// open window
    bool Open();
    /// close window
    void Close();
    
    /// make this window current for GL context
    void MakeCurrent();
    /// swap buffers at end of frame
    void SwapBuffers();
    
    /// updates all windows including events and such
    static void Update();
    
    /// public members, setting them as is will do nothing
    uint32 width;
    uint32 height;
    Core::String title;
protected:

    /// function for key press callbacks
	Ptr<Core::Function<void(int32, int32, int32, int32)>> keyPressCallback;
	/// function for mouse press callbacks
	Ptr<Core::Function<void(int32, int32, int32)>> mousePressCallback;
	/// function for mouse move callbacks
	Ptr<Core::Function<void(float64, float64)>> mouseMoveCallback;
	/// function for mouse enter/leave callbacks
	Ptr<Core::Function<void(bool)>> mouseLeaveEnterCallback;
	/// function for mose scroll callbacks
	Ptr<Core::Function<void(float64, float64)>> mouseScrollCallback;
    
    Ptr<Render::Context> context;
    Ptr<Render::RenderTarget> renderTarget;
    static uint32 GlobalWindowCounter;
};

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetWidth(const uint32 width)
{
    this->width = width;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetHeight(const uint32 height)
{
    this->height = height;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetKeyPressFunction(const Ptr<Core::Function<void(int32, int32, int32, int32)>>& func)
{
	this->keyPressCallback = func;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetMousePressFunction(const Ptr<Core::Function<void(int32, int32, int32)>>& func)
{
	this->mousePressCallback = func;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetMouseMoveFunction(const Ptr<Core::Function<void(float64, float64)>>& func)
{
	this->mouseMoveCallback = func;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetMouseEnterLeaveFunction(const Ptr<Core::Function<void(bool)>>& func)
{
	this->mouseLeaveEnterCallback = func;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Window::SetMouseScrollFunction(const Ptr<Core::Function<void(float64, float64)>>& func)
{
	this->mouseScrollCallback = func;
}

}} // namespace JARVIS::Display