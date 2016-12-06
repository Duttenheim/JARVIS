//------------------------------------------------------------------------------
/**
    @class JARVIS::Core::RenderApplication
 	(C) 2016 See the LICENSE file.
*/
#include "renderapplication.h"
namespace JARVIS {
namespace Core
{
    
//------------------------------------------------------------------------------
/**
*/
RenderApplication::RenderApplication()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
RenderApplication::~RenderApplication()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
RenderApplication::OnSetup()
{
#if J_RENDERER_METAL
    this->sysfunc.StartOSX();
#else
    this->OnSetup();
    this->state = Running;
    while (this->state == Application::Running)
    {
        this->OnFrame();
    }
#endif
    this->OnExit();
}

//------------------------------------------------------------------------------
/**
*/
void
RenderApplication::OnFrame()
{

}

//------------------------------------------------------------------------------
/**
*/
void
RenderApplication::OnExit()
{

}

}}
