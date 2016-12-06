#pragma once
//------------------------------------------------------------------------------
//  @file render/shader.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/shader.h"
namespace JARVIS {
namespace Render
{
class Shader : public JARVIS::GL4::Shader
{};
__Ptr(Shader)
}}
#elif J_RENDERER_METAL
#include "metal/shader.h"
namespace JARVIS {
namespace Render
{
class Shader : public JARVIS::Metal::Shader
{};
__Ptr(Shader)
}}
#else
#error "Shader is not implemented using this renderer!"
#endif