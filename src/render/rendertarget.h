#pragma once
//------------------------------------------------------------------------------
//  @file render/rendertarget.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/rendertarget.h"
namespace JARVIS {
namespace Render
{
class RenderTarget : public JARVIS::GL4::RenderTarget
{};
__Ptr(RenderTarget);
}}
#elif J_RENDERER_METAL
#include "metal/rendertarget.h"
namespace JARVIS {
namespace Render
{
class RenderTarget : public JARVIS::Metal::RenderTarget
{};
__Ptr(RenderTarget);
}}
#else
#error "RenderTarget is not implemented using this renderer!"
#endif