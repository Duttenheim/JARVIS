#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::WindowTest::WindowApp
	
    Opens a window and clears the screen
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "application.h"
#include "window.h"
namespace JARVIS {
namespace WindowTest
{
class WindowApp : public Core::Application
{
public:
    /// constructor
    WindowApp();
    /// destructor
    virtual ~WindowApp();
    
    /// setup context
    void Setup();
    /// implement main loop
    void Run();
    
private:
    Core::Ptr<Render::Window> window;
};

}} // namespace JARVIS::WindowTest