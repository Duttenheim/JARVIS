//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::Application
 	(C) 2015 See the LICENSE file.
*/
#include "application.h"
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
    This enters the application main loop.
*/
void
Application::Start()
{
    this->Setup();
    this->state = Running;
    this->Run();
    this->Exit();
}

//------------------------------------------------------------------------------
/**
    Setup the initial state of your application here.
    Override this function to setup the application yourself.
    
    This setup proceduce could include stuff as:
        Path resolution and path assignments.
        User profile loading.
        Application window title and window setup.
 
*/
void
Application::Setup()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    This is your applications core code.
*/
void
Application::Run()
{
    // empty
}

//------------------------------------------------------------------------------
/**
    Clean up application.
*/
void
Application::Exit()
{
    // empty
}

}}
