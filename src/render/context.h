#pragma once
//------------------------------------------------------------------------------
//  @file render/context.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/context.h"
namespace JARVIS {
namespace Render
{
class Context : public JARVIS::GL4::Context
{};
__Ptr(Context)
}}
#elif J_RENDERER_METAL
#include "metal/context.h"
namespace JARVIS {
namespace Render
{
class Context : public JARVIS::Metal::Context
{};
__Ptr(Context)
}}
#else
#error "Context is not implemented using this renderer!"
#endif