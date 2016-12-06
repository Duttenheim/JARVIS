#pragma once
//------------------------------------------------------------------------------
//  @file resources/renderstatetypes.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------


namespace JARVIS {
namespace Render
{

enum class CullMode : uint8
{
    Front,
    Back,
    None
};

enum class Winding : uint8
{
    Clockwise,
    CounterClockwise
};

enum class DepthMode : uint8
{
    Clip,
    Clamp
};

enum class FillMode : uint8
{
    Fill,
    Lines
};

enum class StencilOp : uint8
{
    Keep,
    Zero,
    Replace,
    IncrementClamp,
    DecrementClamp,
    Invert,
    IncrementWrap,
    DecrementWrap
};

enum class CompareMode : uint8
{
    Never,
    Less,
    Equal,
    LessEqual,
    Greater,
    GreaterEqual,
    NotEqual,
    Always
};

}} // namespace JARVIS::Render