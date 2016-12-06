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
RenderApplication::Start()
{
#if J_RENDERER_METAL
    this->sysfunc.StartOSX();
#else
    Application::Start();
#endif
}

//------------------------------------------------------------------------------
/**
*/
void
RenderApplication::OnSetup()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
RenderApplication::OnFrame()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
RenderApplication::OnExit()
{
    // empty
}

}}
