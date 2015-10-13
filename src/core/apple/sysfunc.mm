//------------------------------------------------------------------------------
/**
    @class JARVIS::Apple::SysFunc
 	(C) 2015 See the LICENSE file.
*/
#include "sysfunc.h"
#include "application.h"

@interface JARVISAppDelegate<NSApplicationDelegate> : NSObject
@end

@implementation JARVISAppDelegate

// have the application delegate launch the application setup procedure
// the MTKView will handle the OnFrame updates...
- (void)applicationDidFinishLaunching:(NSNotification*)aNotification
{
    JARVIS::Core::Application::Instance()->Setup();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender
{
    return YES;
}
@end

namespace JARVIS {
namespace Apple
{
    
//------------------------------------------------------------------------------
/**
*/
SysFunc::SysFunc()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
SysFunc::~SysFunc()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
SysFunc::StartOSX()
{
    this->app = [NSApplication sharedApplication];
    this->appDelegate = [[JARVISAppDelegate alloc] init];
    [this->app setDelegate:this->appDelegate];
    [this->app run];
    
    [this->appDelegate release];
    [this->app release];
}

//------------------------------------------------------------------------------
/**
*/
void
SysFunc::StartIOS()
{

}

}} // namespace Core::Apple
