#pragma once
//------------------------------------------------------------------------------
//  @file render/rendertarget.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/rendertarget.h"
__Wrap(Render, GL4, RenderTarget);
#elif J_RENDERER_METAL
#include "metal/rendertarget.h"
__Wrap(Render, Metal, RenderTarget);
#else
#error "RenderTarget is not implemented using this renderer!"
#endif