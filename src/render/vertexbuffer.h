#pragma once
//------------------------------------------------------------------------------
//  @file render/vertexbuffer.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/vertexbuffer.h"
__Wrap(Render, GL4, VertexBuffer);
#elif J_RENDERER_METAL
#include "metal/vertexbuffer.h"
__Wrap(Render, Metal, VertexBuffer);
#else
#error "VertexBuffer is not implemented using this renderer!"
#endif