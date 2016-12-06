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
    void OnSetup();
    /// implement main loop
    void OnFrame();
    /// exit app
    void OnExit();
    
private:
    Render::WindowPtr window;
    Render::RenderTargetPtr rt;
    Render::PipelineStatePtr pipeline;
    Render::RenderStatePtr renderState;
    Render::VertexBufferPtr vbo;
    Render::UniformBufferPtr ubo;
    Render::Primitive prim;
    
    float rot;
    Render::UniformBuffer::UniformMember member;
    
};

}} // namespace JARVIS::WindowTest