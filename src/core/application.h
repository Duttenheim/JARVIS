#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Application
	
    Application entry point. 
    Inherit this class in the project and implement own Start, Run and Exit callbacks.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "sysfunc.h"
#include "appargs.h"
namespace JARVIS {
namespace Core
{

class Application
{
    __SingletonDecl(Application)
public:

    enum State
    {
        Initial,
        Running,
        Exiting
    };
    
    /// constructor
    Application();
    /// destructor
    virtual ~Application();
    
    /// setup application arguments
    void SetAppArgs(const char** argv, const uint32 argc);
    
    /// start application
    void Start();
    /// stop application
    void Stop();
    
    /// setup the application context
    virtual void OnSetup();
    /// run the application code
    virtual void OnFrame();
    /// exit function
    virtual void OnExit();
    
protected:
    friend class JARVISAppDelegate;
    friend class JARVISViewDelegate;
    
	SysFunc sysfunc;
    
    AppArgs args;
    State state;
};

//------------------------------------------------------------------------------
/**
*/
inline void
Application::Stop()
{
    this->state = Exiting;
}

}} // namespace JARVIS::Core