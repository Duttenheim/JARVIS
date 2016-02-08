#pragma once
//------------------------------------------------------------------------------
//  @file render/renderstate.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/renderstate.h"
namespace JARVIS {
namespace Render
{
class RenderState : public JARVIS::GL4::RenderState
{};
__Ptr(RenderState)
}}
#elif J_RENDERER_METAL
#include "metal/renderstate.h"
namespace JARVIS {
namespace Render
{
class RenderState : public JARVIS::Metal::RenderState
{};
__Ptr(RenderState)
}}
#else
#error "RenderState is not implemented using this renderer!"
#endif