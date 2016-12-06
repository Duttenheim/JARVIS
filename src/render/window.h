#pragma once
//------------------------------------------------------------------------------
//  @file render/window.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/window.h"
namespace JARVIS {
namespace Render
{
class Window : public JARVIS::GL4::Window
{};
__Ptr(Window)
}}
#elif J_RENDERER_METAL
#include "metal/window.h"
namespace JARVIS {
namespace Render
{
class Window : public JARVIS::Metal::Window
{};
__Ptr(Window)
}}
#else
#error "Window is not implemented using this renderer!"
#endif