//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::Application
 	(C) 2015 See the LICENSE file.
*/
#include "application.h"
#include "io/assigns.h"
namespace JARVIS {
namespace Core
{
    
__SingletonDef(Application);
//------------------------------------------------------------------------------
/**
*/
Application::Application() :
    state(Initial)
{
    __SingletonCtor();
}

//------------------------------------------------------------------------------
/**
*/
Application::~Application()
{
    __SingletonDtor();
}
//------------------------------------------------------------------------------
/**
*/
void
Application::SetAppArgs(const char** argv, const uint32 argc)
{
    this->args.Set(argv, argc);
}

//------------------------------------------------------------------------------
/**
    This enters the application main loop.
*/
void
Application::Start()
{
    this->state = Running;
    this->OnSetup();
    while (this->state == Application::Running)
    {
        this->OnFrame();
    }
    this->OnExit();
}

//------------------------------------------------------------------------------
/**
    Setup the initial state of your application here.
    Override this function to setup the application yourself.
    
    Remember to run this yourself since it will retrieve the binary directory.
    
    This setup proceduce could include stuff as:
        Path resolution and path assignments.
        User profile loading.
        Application window title and window setup.
 
*/
void
Application::OnSetup()
{
    Assigns::NewAssignment("root", this->sysfunc.BinDir());
}

//------------------------------------------------------------------------------
/**
    This is your applications core code.
*/
void
Application::OnFrame()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Clean up application.
*/
void
Application::OnExit()
{
    // empty
}

}}
