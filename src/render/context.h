#pragma once
//------------------------------------------------------------------------------
//  @file render/context.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/context.h"
__Wrap(Render, GL4, Context);
#elif J_RENDERER_METAL
#include "metal/context.h"
__Wrap(Render, Metal, Context);
#else
#error "Context is not implemented using this renderer!"
#endif