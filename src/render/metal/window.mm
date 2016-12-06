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

@implementation JARVISMTKView
- (BOOL)isOpaque {
    return YES;
}

- (BOOL)canBecomeKeyView {
    return YES;
}

- (BOOL)acceptsFirstResponder {
    return YES;
}
@end

namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
Window::Window() :
    nsWindow(nullptr),
    view(nullptr)
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
    
    // create window
    this->nsWindow = [[NSWindow alloc]initWithContentRect:NSMakeRect(0, 0, this->width, this->height) styleMask:NSTitledWindowMask backing:NSBackingStoreBuffered defer:NO];
    [this->nsWindow setTitle: [[NSString alloc] initWithCString: this->title.CharPtr() encoding:NSUTF8StringEncoding]];
    
    if (this->nsWindow != nil)
    {
        // create context!
        this->context = Metal::Context::Create();
        this->context->Setup();
        
        // setup view for Metal display
        this->viewDelegate = [[JARVISViewDelegate alloc] init];
        this->view = [[JARVISMTKView alloc] init];
        [this->view setDelegate:this->viewDelegate];
        [this->view setPreferredFramesPerSecond:60];
        [this->view setWantsLayer:YES];
        [this->view setDevice:this->context->device];
        [this->view setSampleCount:8];
        [this->view setColorPixelFormat:MTLPixelFormatBGRA8Unorm];
        [this->view setDepthStencilPixelFormat:MTLPixelFormatDepth32Float_Stencil8];
        [this->nsWindow setContentView:this->view];
        [this->nsWindow makeKeyAndOrderFront:nil];
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
    this->context->Present(this);
}

//------------------------------------------------------------------------------
/**
*/
void
Window::Update()
{
    this->context->NewFrame();
}

}} // namespace JARVIS::Metal
