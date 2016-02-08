#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::WindowTest::WindowApp
	
    Opens a window and clears the screen
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "renderapplication.h"
#include "window.h"
namespace JARVIS {
namespace WindowTest
{
class WindowApp : public Core::RenderApplication
{
public:
    /// constructor
    WindowApp();
    /// destructor
    virtual ~WindowApp();
    
    /// setup context
    void Setup();
    /// implement main loop
    void OnFrame();
    /// exit app
    void Exit();
    
private:
    Render::WindowPtr window;
    Render::RenderTargetPtr rt;
    Render::PipelineStatePtr pipeline;
    Render::RenderStatePtr renderState;
    Render::VertexBufferPtr vbo;
    Render::Primitive prim;
    
};

}} // namespace JARVIS::WindowTest