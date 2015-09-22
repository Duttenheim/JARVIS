#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::Window
	
    Implements a drawable surface using Metal.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "types.h"
#include "display/window.h"
namespace JARVIS {
namespace Metal
{
class Window : public Base::Window
{
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
    static void Update();
    
private:
    OBJC_POINTER(NSWindow) nsWindow;
    OBJC_POINTER(CAMetalLayer) defaultRenderTarget;
};

}} // namespace JARVIS::Metal