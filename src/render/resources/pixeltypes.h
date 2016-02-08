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

//------------------------------------------------------------------------------
/**
*/
inline uint32
PixelSize(Render::PixelFormat format)
{
    switch (format)
    {
        case PixelFormat::A8_UNorm:         return 1;
        case PixelFormat::R8_UNorm:         return 1;
        case PixelFormat::R8_UNorm_sRGB:    return 1;
        case PixelFormat::R8_SNorm:         return 1;
        case PixelFormat::R8_UInt:          return 1;
        case PixelFormat::R8_SInt:          return 1;
        case PixelFormat::R16_UNorm:        return 2;
        case PixelFormat::R16_SNorm:        return 2;
        case PixelFormat::R16_UInt:         return 2;
        case PixelFormat::R16_SInt:         return 2;
        case PixelFormat::R16_Float:        return 2;
        case PixelFormat::R32_UInt:         return 4;
        case PixelFormat::R32_SInt:         return 4;
        case PixelFormat::R32_Float:        return 4;
        
        case PixelFormat::RG8_UNorm:        return 2;
        case PixelFormat::RG8_UNorm_sRGB:   return 2;
        case PixelFormat::RG8_SNorm:        return 2;
        case PixelFormat::RG8_UInt:         return 2;
        case PixelFormat::RG8_SInt:         return 2;
        
        case PixelFormat::RG16_UNorm:       return 4;
        case PixelFormat::RG16_SNorm:       return 4;
        case PixelFormat::RG16_UInt:        return 4;
        case PixelFormat::RG16_SInt:        return 4;
        case PixelFormat::RG16_Float:       return 4;
        case PixelFormat::RG32_UInt:        return 8;
        case PixelFormat::RG32_SInt:        return 8;
        case PixelFormat::RG32_Float:       return 8;
        
        case PixelFormat::RGBA8_UNorm:      return 4;
        case PixelFormat::RGBA8_UNorm_sRGB: return 4;
        case PixelFormat::RGBA8_SNorm:      return 4;
        case PixelFormat::RGBA8_UInt:       return 4;
        case PixelFormat::RGBA8_SInt:       return 4;
        case PixelFormat::BGRA8_UNorm:      return 4;
        case PixelFormat::BGRA8_UNorm_sRGB: return 4;
        case PixelFormat::RGBA16_UNorm:     return 8;
        case PixelFormat::RGBA16_SNorm:     return 8;
        case PixelFormat::RGBA16_UInt:      return 8;
        case PixelFormat::RGBA16_SInt:      return 8;
        case PixelFormat::RGBA16_Float:     return 8;
        case PixelFormat::RGBA32_UInt:      return 16;
        case PixelFormat::RGBA32_SInt:      return 16;
        case PixelFormat::RGBA32_Float:     return 16;
        
        case PixelFormat::BC1:              return 8;
        case PixelFormat::BC1_sRGB:         return 8;
        case PixelFormat::BC2:              return 16;
        case PixelFormat::BC2_sRGB:         return 16;
        case PixelFormat::BC3:              return 16;
        case PixelFormat::BC3_sRGB:         return 16;
        case PixelFormat::BC7:              return 16;
        case PixelFormat::BC7_sRGB:         return 16;
    }
}

}} // namespace JARVIS::Render