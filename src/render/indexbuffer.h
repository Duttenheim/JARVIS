#pragma once
//------------------------------------------------------------------------------
//  @file render/indexbuffer.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/indexbuffer.h"
__Wrap(Render, GL4, IndexBuffer);
#elif J_RENDERER_METAL
#include "metal/indexbuffer.h"
__Wrap(Render, Metal, IndexBuffer);
#else
#error "IndexBuffer is not implemented using this renderer!"
#endif