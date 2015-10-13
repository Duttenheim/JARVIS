#pragma once
//------------------------------------------------------------------------------
//  @file resources/pixeltypes.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

namespace JARVIS {
namespace Render
{

enum class PixelFormat : uint8
{
    A8_UNorm,
    R8_UNorm,
    R8_UNorm_sRGB,
    R8_SNorm,
    R8_UInt,
    R8_SInt,
    R16_UNorm,
    R16_SNorm,
    R16_UInt,
    R16_SInt,
    R16_Float,
    R32_UInt,
    R32_SInt,
    R32_Float,
    
    RG8_UNorm,
    RG8_UNorm_sRGB,
    RG8_SNorm,
    RG8_UInt,
    RG8_SInt,
    
    RG16_UNorm,
    RG16_SNorm,
    RG16_UInt,
    RG16_SInt,
    RG16_Float,
    RG32_UInt,
    RG32_SInt,
    RG32_Float,
    
    RGBA8_UNorm,
    RGBA8_UNorm_sRGB,
    RGBA8_SNorm,
    RGBA8_UInt,
    RGBA8_SInt,
    BGRA8_UNorm,
    BGRA8_UNorm_sRGB,
    RGBA16_UNorm,
    RGBA16_SNorm,
    RGBA16_UInt,
    RGBA16_SInt,
    RGBA16_Float,
    RGBA32_UInt,
    RGBA32_SInt,
    RGBA32_Float,
    
    BC1,
    BC1_sRGB,
    BC2,
    BC2_sRGB,
    BC3,
    BC3_sRGB,
    BC7,
    BC7_sRGB
};

}} // namespace JARVIS::Render