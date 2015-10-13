//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::Window
 	(C) 2015 See the LICENSE file.
*/
#include "window.h"
#include "application.h"
#include "resources/pixeltypes.h"

@interface JARVISViewDelegate<MTKViewDelegate> : NSObject
@end

@implementation JARVISViewDelegate
- (void)mtkView:(nonnull MTKView*)view drawableSizeWillChange:(CGSize)size
{

}

// hmm, what if we have more than one window?
- (void)drawInMTKView:(nonnull MTKView*)view
{
    @autoreleasepool
    {
        JARVIS::Core::Application::Instance()->OnFrame();
    }
}
@end

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
    rect.origin = NSPoint{0, 0};
    rect.size = NSSize{(float64)this->width, (float64)this->height};
    this->nsWindow = [[[NSWindow alloc]initWithContentRect:rect styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO] autorelease];
    [this->nsWindow setTitle: [[NSString alloc] initWithCString: this->title.CharPtr() encoding:NSUnicodeStringEncoding]];
    [this->nsWindow makeKeyAndOrderFront:NSApp];
    
    if (this->nsWindow != nil)
    {
        // create context!
        this->context = Metal::Context::Create();
        this->context->Setup();
        
        // setup view for Metal display
        this->viewDelegate = [[JARVISViewDelegate alloc] init];
        this->view = [[MTKView alloc] init];
        [this->view setDelegate:this->viewDelegate];
        [this->view setPreferredFramesPerSecond:60];
        [this->view setDevice:this->context->device];
        [this->view setColorPixelFormat: (MTLPixelFormat)Types::PixelFormatFlag(Render::PixelFormat::BGRA8_UNorm_sRGB)];
        [this->view setDepthStencilPixelFormat:MTLPixelFormatDepth32Float];
        [this->nsWindow setContentView:this->view];
        
        Base::Window::Open();
    }
    return this->nsWindow != nil;
}

//------------------------------------------------------------------------------
/**
*/
void
Window::Close()
{
    Base::Window::Close();
}

//------------------------------------------------------------------------------
/**
*/
void
Window::MakeCurrent()
{
    Base::Window::MakeCurrent();
}

//------------------------------------------------------------------------------
/**
*/
void
Window::SwapBuffers()
{
    Base::Window::SwapBuffers();
    [this->context->cmdBuffer commit];
    [this->context->cmdBuffer presentDrawable:this->view.currentDrawable];
}

//------------------------------------------------------------------------------
/**
*/
void
Window::Update()
{
}

}} // namespace JARVIS::Metal
