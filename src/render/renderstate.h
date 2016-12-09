#pragma once
//------------------------------------------------------------------------------
//  @file render/renderstate.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/renderstate.h"
__Wrap(Render, GL4, RenderState);
#elif J_RENDERER_METAL
#include "metal/renderstate.h"
__Wrap(Render, Metal, RenderState);
#else
#error "RenderState is not implemented using this renderer!"
#endif