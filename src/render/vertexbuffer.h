#pragma once
//------------------------------------------------------------------------------
//  @file render/vertexbuffer.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/vertexbuffer.h"
namespace JARVIS {
namespace Render {
using VertexBuffer = JARVIS::GL4::VertexBuffer;
}}
#elif J_RENDERER_METAL
#include "metal/vertexbuffer.h"
namespace JARVIS {
namespace Render {
using VertexBuffer = JARVIS::Metal::VertexBuffer;
}}
#else
#error "VertexBuffer is not implemented using this renderer!"
#endif