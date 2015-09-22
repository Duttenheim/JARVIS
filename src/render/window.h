#pragma once
//------------------------------------------------------------------------------
//  @file render/window.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/window.h"
namespace JARVIS {
namespace Render {
using Window = JARVIS::GL4::Window;
}}
#elif J_RENDERER_METAL
#include "metal/window.h"
namespace JARVIS {
namespace Render {
using Window = JARVIS::Metal::Window;
}}
#else
#error "Window is not implemented using this renderer!"
#endif