//------------------------------------------------------------------------------
/**
    @class JARVIS::WindowTest::WindowApp
 	(C) 2015 See the LICENSE file.
*/
#include "windowapp.h"
#include "threads/threading.h"
namespace JARVIS {
namespace WindowTest
{

//------------------------------------------------------------------------------
/**
*/
WindowApp::WindowApp()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
WindowApp::~WindowApp()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
WindowApp::Setup()
{
    this->window = Render::Window::Create();
    this->window->Open();
    auto func = Core::Functional::Lambda([this](int32, int32, int32) -> void
    {
        this->state = Application::Exiting;
    });
    this->window->SetMousePressFunction(func);
    
    this->window->MakeCurrent();
}

//------------------------------------------------------------------------------
/**
*/
void
WindowApp::Run()
{
    while (this->state == Application::Running)
    {
        this->window->Update();
        this->window->SwapBuffers();
    }
    this->window->Close();
}

}} // namespace JARVIS::WindowTest
