#pragma once
//------------------------------------------------------------------------------
//  @file render/depthstenciltarget.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/depthstenciltarget.h"
__Wrap(Render, GL4, DepthStencilTarget);
#elif J_RENDERER_METAL
#include "metal/depthstenciltarget.h"
__Wrap(Render, Metal, DepthStencilTarget);
#else
#error "DepthStencilTarget is not implemented using this renderer!"
#endif