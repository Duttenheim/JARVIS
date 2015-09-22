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
    /// tell the application to quit
    void Quit();
    
protected:

    /// setup the application context
    virtual void Setup();
    /// run the application code
    virtual void Run();
    /// exit function
    virtual void Exit();
    
    State state;
};

//------------------------------------------------------------------------------
/**
*/
inline void
Application::Quit()
{
    this->state = Exiting;
}

}} // namespace JARVIS::Core