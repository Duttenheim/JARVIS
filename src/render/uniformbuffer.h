#pragma once
//------------------------------------------------------------------------------
//  @file render/uniformbuffer.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/uniformbuffer.h"
__Wrap(Render, GL4, UniformBuffer);
#elif J_RENDERER_METAL
#include "metal/uniformbuffer.h"
__Wrap(Render, Metal, UniformBuffer);
#else
#error "UniformBuffer is not implemented using this renderer!"
#endif