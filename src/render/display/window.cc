//------------------------------------------------------------------------------
/**
    @class JARVIS::Display::Window
 	(C) 2015 See the LICENSE file.
*/
#include "config.h"
#include "window.h"
#include <string>
namespace JARVIS {
namespace Base
{

#ifdef __WIN32__
#define APICALLTYPE __stdcall
#else
#define APICALLTYPE
#endif


    
uint32 Window::GlobalWindowCounter = 0;

//------------------------------------------------------------------------------
/**
*/
Window::Window() :
    width(1024),
    height(768)
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
    Returns false because this base class doesn't really create a window.
*/
bool
Window::Open()
{
    Window::GlobalWindowCounter++;
    return false;
}

//------------------------------------------------------------------------------
/**
*/
void
Window::Close()
{
    Window::GlobalWindowCounter--;
}

//------------------------------------------------------------------------------
/**
*/
void
Window::MakeCurrent()
{
    // empty, override in subclass
}

//------------------------------------------------------------------------------
/**
*/
void
Window::SwapBuffers()
{
    // empty, override in subclass
}


//------------------------------------------------------------------------------
/**
*/
void
Window::Update()
{
    // empty, override in subclass
}

}} // namespace JARVIS::Render
