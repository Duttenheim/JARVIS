#pragma once
//------------------------------------------------------------------------------
//  @file render/indexbuffer.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/indexbuffer.h"
namespace JARVIS {
namespace Render
{
class IndexBuffer : public JARVIS::GL4::IndexBuffer
{};
}}
#elif J_RENDERER_METAL
#include "metal/indexbuffer.h"
namespace JARVIS {
namespace Render
{
class IndexBuffer : public JARVIS::Metal::IndexBuffer
{};
}}
#else
#error "IndexBuffer is not implemented using this renderer!"
#endif