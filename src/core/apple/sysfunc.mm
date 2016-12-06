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
    JARVIS::Core::Application::Instance()->OnSetup();
}

- (BOOL)applicationShouldTerminateAfterLastWindowClosed:(NSApplication*)sender
{
    return YES;
}
@end

namespace CoreFoundation
{
#include <CoreFoundation/CoreFoundation.h>
}

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
    Start OSX driven application using their application system and loop.
    Note: this is only useful when using Metal.
*/
void
SysFunc::StartOSX()
{
    this->app = [NSApplication sharedApplication];
    this->appDelegate = [[JARVISAppDelegate alloc] init];
    [NSApp setDelegate:this->appDelegate];
    [NSApp run];
}

//------------------------------------------------------------------------------
/**
    Start OSX driven application using their application system and loop.
    Note: this is only useful when using Metal.
    
 
    TODO: test me
*/
void
SysFunc::StartIOS()
{
    this->app = [NSApplication sharedApplication];
    this->appDelegate = [[JARVISAppDelegate alloc] init];
    [NSApp setDelegate:this->appDelegate];
    [NSApp run];
}

//------------------------------------------------------------------------------
/**
    Finds the directory where the executing binary is located.
*/
Core::String
SysFunc::BinDir()
{
    char buf[MAXPATHLEN];
    CFBundleRef mainBundle = CFBundleGetMainBundle();
    CFURLRef bundleURL = CFBundleCopyBundleURL(mainBundle);
    CFURLGetFileSystemRepresentation(bundleURL, true, (UInt8*)buf, MAXPATHLEN);
    Core::String result = buf;
    result.Replace('\\', '/');  // yeah, like this is EVER needed...
    result = result.ExtractToIndex(result.FindLast('/') + 1);
    return Core::String("file://") + result;
}

}} // namespace Core::Apple
