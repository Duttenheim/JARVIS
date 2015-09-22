//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::Window
 	(C) 2015 See the LICENSE file.
*/
#include "window.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
Window::Window() :
    nsWindow(nil)
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
    j_assert(this->nsWindow == nil);
    NSRect rect;
    rect.size = NSSize{(float64)this->width, (float64)this->height};
    this->nsWindow = [[NSWindow alloc]initWithContentRect:rect styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO ];
    [this->nsWindow setTitle: [[NSString alloc] initWithCString: this->title.CharPtr() encoding:NSUnicodeStringEncoding]];
    return this->nsWindow != nil;
}

//------------------------------------------------------------------------------
/**
*/
void
Window::Close()
{

}

//------------------------------------------------------------------------------
/**
*/
void
Window::MakeCurrent()
{

}

//------------------------------------------------------------------------------
/**
*/
void
Window::SwapBuffers()
{

}

//------------------------------------------------------------------------------
/**
*/
void
Window::Update()
{
}

}}
