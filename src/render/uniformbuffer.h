#pragma once
//------------------------------------------------------------------------------
//  @file render/uniformbuffer.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/uniformbuffer.h"
namespace JARVIS {
namespace Render
{
class UniformBuffer : public JARVIS::GL4::UniformBuffer
{};
__Ptr(UniformBuffer)
}}
#elif J_RENDERER_METAL
#include "metal/uniformbuffer.h"
namespace JARVIS {
namespace Render
{
class UniformBuffer : public JARVIS::Metal::UniformBuffer
{};
__Ptr(UniformBuffer)
}}
#else
#error "UniformBuffer is not implemented using this renderer!"
#endif