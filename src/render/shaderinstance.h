#pragma once
//------------------------------------------------------------------------------
//  @file render/shaderinstance.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/shaderinstance.h"
namespace JARVIS {
namespace Render {
using ShaderInstance = JARVIS::GL4::ShaderInstance;
}}
#elif J_RENDERER_METAL
#include "metal/shaderinstance.h"
namespace JARVIS {
namespace Render {
using ShaderInstance = JARVIS::Metal::ShaderInstance;
}}
#else
#error "ShaderInstance is not implemented using this renderer!"
#endif