#pragma once
//------------------------------------------------------------------------------
//  @file render/pipelinestate.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#if J_RENDERER_GL4
#include "gl4/pipelinestate.h"
namespace JARVIS {
namespace Render
{
class PipelineState : public JARVIS::GL4::PipelineState
{};
}}
#elif J_RENDERER_METAL
#include "metal/pipelinestate.h"
namespace JARVIS {
namespace Render
{
class PipelineState : public JARVIS::Metal::PipelineState
{};
}}
#else
#error "PipelineState is not implemented using this renderer!"
#endif