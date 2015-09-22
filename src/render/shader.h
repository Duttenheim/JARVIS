#pragma once
//------------------------------------------------------------------------------
//  @file render/shader.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/shader.h"
namespace JARVIS {
namespace Render {
using Shader = JARVIS::GL4::Shader;
}}
#elif J_RENDERER_METAL
#include "metal/shader.h"
namespace JARVIS {
namespace Render {
using Shader = JARVIS::Metal::Shader;
}}
#else
#error "Shader is not implemented using this renderer!"
#endif