#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Apple::SysFunc
	
    Implements Apple-based system functions, which are used to start an application.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Apple
{
class SysFunc
{
public:
    /// constructor
    SysFunc();
    /// destructor
    virtual ~SysFunc();
    
    /// start as an OS X app
    void StartOSX();
    /// start as an iOS app
    void StartIOS();
    
private:
    OBJC_POINTER(NSApplication) app;
    OBJC_ID appDelegate;
};

}} // namespace JARVIS::Apple