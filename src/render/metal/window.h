#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::Window
	
    Implements a drawable surface using Metal.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "display/window.h"
#include "types.h"

#if __OBJC__
@interface JARVISMTKView: MTKView
@end
#endif

namespace JARVIS {
namespace Metal
{
class RenderTarget;
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
    friend class Metal::RenderTarget;
    friend class Metal::Context;
    OBJC_POINTER(NSWindow) nsWindow;
    OBJC_ID viewDelegate;
    OBJC_POINTER(JARVISMTKView) view;
    OBJC_POINTER(CAMetalLayer) defaultRenderTarget;
};

}} // namespace JARVIS::Metal