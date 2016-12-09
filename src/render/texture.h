#pragma once
//------------------------------------------------------------------------------
//  @file render/texture.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/texture.h"
__Wrap(Render, GL4, Texture);
#elif J_RENDERER_METAL
#include "metal/texture.h"
__Wrap(Render, Metal, Texture);
#else
#error "Texture is not implemented using this renderer!"
#endif