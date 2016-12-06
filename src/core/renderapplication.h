#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::RenderApplication
	
    Implements a rendering application which might go through,
    the system specific window system to start the application and start a main loop
	
	(C) 2016 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "application.h"
namespace JARVIS {
namespace Core
{
class RenderApplication : public Application
{
    __SingletonDecl(RenderApplication);
public:
    /// constructor
    RenderApplication();
    /// destructor
    virtual ~RenderApplication();
    
    /// overload start
    void Start();
    /// overload stop
    void Stop();
    
    /// setup the application context
    virtual void OnSetup();
    /// run the application code
    virtual void OnFrame();
    /// exit function
    virtual void OnExit();
    
private:
};

}} // namespace JARVIS::Core