#pragma once
//------------------------------------------------------------------------------
//  @file render/shaderstate.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/shaderstate.h"
namespace JARVIS {
namespace Render
{
class ShaderState : public JARVIS::GL4::ShaderState
{};
__Ptr(ShaderState)
}}
#elif J_RENDERER_METAL
#include "metal/shaderstate.h"
namespace JARVIS {
namespace Render
{
class ShaderState : public JARVIS::Metal::ShaderState
{};
__Ptr(ShaderState)
}}
#else
#error "ShaderState is not implemented using this renderer!"
#endif