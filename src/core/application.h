#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Application
	
    Application entry point. 
    Inerhit this class in the project and implement own Start, Run and Exit callbacks.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
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
    /// setup the application context
    virtual void Setup();
    /// main loop function
    virtual void Run();
    /// exit function
    virtual void Exit();
    
    /// tell the application to quit
    void Quit();
    
protected:
    State state;
};

//------------------------------------------------------------------------------
/**
*/
void
Application::Quit()
{
    this->state = Exiting;
}

}} // namespace JARVIS::Core