#pragma once
//------------------------------------------------------------------------------
//  @file resources/vertextypes.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

namespace JARVIS {
namespace Render
{

enum class ComponentType : uint8
{
    UByte,          // vertex data is unsigned bytes
    Byte,           // vertex data is signed bytes
    UInt,           // vertex data is unsigned integer
    Int,            // vertex data is integer
    UShort,         // vertex data is 16 bit unsigned integer
    Short,          // vertex data is 16 bit signed integer
    Float,          // vertex data is floats
    Double         // vertex data is doubles
};

}} // namespace JARVIS::Render