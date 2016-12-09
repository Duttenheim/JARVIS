#pragma once
//------------------------------------------------------------------------------
//  @file render/window.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/window.h"
__Wrap(Render, GL4, Window);
#elif J_RENDERER_METAL
__Wrap(Render, Metal, Window);
#else
#error "Window is not implemented using this renderer!"
#endif