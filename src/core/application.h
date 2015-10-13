#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Application
	
    Application entry point. 
    Inerhit this class in the project and implement own Start, Run and Exit callbacks.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#if __APPLE__
#include "apple/sysfunc.h"
#endif
namespace JARVIS {
namespace Core
{

class Application
{
    __SingletonDecl(Application);
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
    
    /// start application
    void Start();
    /// stop application
    void Stop();
    
    /// setup the application context
    virtual void Setup();
    /// run the application code
    virtual void OnFrame();
    /// exit function
    virtual void Exit();
    
protected:
    friend class JARVISAppDelegate;
    friend class JARVISViewDelegate;
    
#if __APPLE__
    Apple::SysFunc sysfunc;
#endif
    
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