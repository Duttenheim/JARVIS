#pragma once
//------------------------------------------------------------------------------
//  @file render/shaderstate.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/shaderstate.h"
__Wrap(Render, GL4, ShaderState);
#elif J_RENDERER_METAL
#include "metal/shaderstate.h"
__Wrap(Render, Metal, ShaderState);
#else
#error "ShaderState is not implemented using this renderer!"
#endif