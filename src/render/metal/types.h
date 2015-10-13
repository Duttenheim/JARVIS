#pragma once
//------------------------------------------------------------------------------
//  @file render/metal/types.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------
#include "resources/pixeltypes.h"
#include "resources/vertextypes.h"
#include "resources/primitive.h"
#include "resources/buffertypes.h"
#include "resources/renderstatetypes.h"
#include "resources/blendstate.h"
#ifndef __OBJC__
typedef void* MTLDevice;
typedef void* MTLCommandQueue;
typedef void* MTLTexture;
typedef void* MTLBuffer;
typedef void* CAMetalLayer;
#endif

#ifdef __OBJC__
    // define unsupported formats to use some fallback...
    #if TARGET_OS_MAC
        #define MTLPixelFormatR8Unorm_sRGB  MTLPixelFormatR8Unorm
        #define MTLPixelFormatRG8Unorm_sRGB MTLPixelFormatRG8Unorm
    #elif TARGET_OS_IPHONE
        #define MTLPixelFormatBC1_RGBA      MTLPixelFormatRGBA8Unorm
        #define MTLPixelFormatBC1_RGBA_sRGB MTLPixelFormatRGBA8Unorm
        #define MTLPixelFormatBC2_RGBA      MTLPixelFormatRGBA8Unorm
        #define MTLPixelFormatBC2_RGBA_sRGB MTLPixelFormatRGBA8Unorm
        #define MTLPixelFormatBC3_RGBA      MTLPixelFormatRGBA8Unorm
        #define MTLPixelFormatBC3_RGBA_sRGB MTLPixelFormatRGBA8Unorm
        #define MTLPixelFormatBC7_RGBA      MTLPixelFormatRGBA8Unorm
        #define MTLPixelFormatBC7_RGBA_sRGB MTLPixelFormatRGBA8Unorm
    #endif


namespace JARVIS {
namespace Metal {
namespace Types
{
//------------------------------------------------------------------------------
/**
*/
inline MTLPixelFormat
PixelFormatFlag(Render::PixelFormat format)
{
    using namespace Render;
    switch (format)
    {
        case PixelFormat::A8_UNorm:         return MTLPixelFormatA8Unorm;
        case PixelFormat::R8_UNorm:         return MTLPixelFormatR8Unorm;
        case PixelFormat::R8_UNorm_sRGB:    return MTLPixelFormatR8Unorm_sRGB;
        case PixelFormat::R8_SNorm:         return MTLPixelFormatR8Snorm;
        case PixelFormat::R8_UInt:          return MTLPixelFormatR8Uint;
        case PixelFormat::R8_SInt:          return MTLPixelFormatR8Sint;
        case PixelFormat::R16_UNorm:        return MTLPixelFormatR16Unorm;
        case PixelFormat::R16_SNorm:        return MTLPixelFormatR16Snorm;
        case PixelFormat::R16_UInt:         return MTLPixelFormatR16Uint;
        case PixelFormat::R16_SInt:         return MTLPixelFormatR16Sint;
        case PixelFormat::R16_Float:        return MTLPixelFormatR16Float;
        case PixelFormat::R32_UInt:         return MTLPixelFormatR32Uint;
        case PixelFormat::R32_SInt:         return MTLPixelFormatR32Sint;
        case PixelFormat::R32_Float:        return MTLPixelFormatR32Float;
        
        case PixelFormat::RG8_UNorm:        return MTLPixelFormatRG8Unorm;
        case PixelFormat::RG8_UNorm_sRGB:   return MTLPixelFormatRG8Unorm_sRGB;
        case PixelFormat::RG8_SNorm:        return MTLPixelFormatRG8Snorm;
        case PixelFormat::RG8_UInt:         return MTLPixelFormatRG8Uint;
        case PixelFormat::RG8_SInt:         return MTLPixelFormatRG8Sint;
        
        case PixelFormat::RG16_UNorm:       return MTLPixelFormatRG16Unorm;
        case PixelFormat::RG16_SNorm:       return MTLPixelFormatRG16Snorm;
        case PixelFormat::RG16_UInt:        return MTLPixelFormatRG16Uint;
        case PixelFormat::RG16_SInt:        return MTLPixelFormatRG16Sint;
        case PixelFormat::RG16_Float:       return MTLPixelFormatRG16Float;
        case PixelFormat::RG32_UInt:        return MTLPixelFormatRG32Uint;
        case PixelFormat::RG32_SInt:        return MTLPixelFormatRG32Sint;
        case PixelFormat::RG32_Float:       return MTLPixelFormatRG32Float;
        
        case PixelFormat::RGBA8_UNorm:      return MTLPixelFormatRGBA8Unorm;
        case PixelFormat::RGBA8_UNorm_sRGB: return MTLPixelFormatRGBA8Unorm_sRGB;
        case PixelFormat::RGBA8_SNorm:      return MTLPixelFormatRGBA8Snorm;
        case PixelFormat::RGBA8_UInt:       return MTLPixelFormatRGBA8Uint;
        case PixelFormat::RGBA8_SInt:       return MTLPixelFormatRGBA8Sint;
        case PixelFormat::BGRA8_UNorm:      return MTLPixelFormatBGRA8Unorm;
        case PixelFormat::BGRA8_UNorm_sRGB: return MTLPixelFormatBGRA8Unorm_sRGB;
        case PixelFormat::RGBA16_UNorm:     return MTLPixelFormatRGBA16Unorm;
        case PixelFormat::RGBA16_SNorm:     return MTLPixelFormatRGBA16Snorm;
        case PixelFormat::RGBA16_UInt:      return MTLPixelFormatRGBA16Uint;
        case PixelFormat::RGBA16_SInt:      return MTLPixelFormatRGBA16Sint;
        case PixelFormat::RGBA16_Float:     return MTLPixelFormatRGBA16Float;
        case PixelFormat::RGBA32_UInt:      return MTLPixelFormatRGBA32Uint;
        case PixelFormat::RGBA32_SInt:      return MTLPixelFormatRGBA32Sint;
        case PixelFormat::RGBA32_Float:     return MTLPixelFormatRGBA32Float;
        
        case PixelFormat::BC1:              return MTLPixelFormatBC1_RGBA;
        case PixelFormat::BC1_sRGB:         return MTLPixelFormatBC1_RGBA_sRGB;
        case PixelFormat::BC2:              return MTLPixelFormatBC2_RGBA;
        case PixelFormat::BC2_sRGB:         return MTLPixelFormatBC2_RGBA_sRGB;
        case PixelFormat::BC3:              return MTLPixelFormatBC3_RGBA;
        case PixelFormat::BC3_sRGB:         return MTLPixelFormatBC3_RGBA_sRGB;
        case PixelFormat::BC7:              return MTLPixelFormatBC7_RGBAUnorm;
        case PixelFormat::BC7_sRGB:         return MTLPixelFormatBC7_RGBAUnorm_sRGB;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline MTLPrimitiveType
PrimitiveTopologyFlag(Render::Primitive::Topology topo)
{
    switch (topo)
    {
        case Render::Primitive::Topology::Point:            return MTLPrimitiveTypePoint;
        case Render::Primitive::Topology::Line:             return MTLPrimitiveTypeLine;
        case Render::Primitive::Topology::LineStrip:        return MTLPrimitiveTypeLineStrip;
        case Render::Primitive::Topology::Triangle:         return MTLPrimitiveTypeTriangle;
        case Render::Primitive::Topology::TriangleStrip:    return MTLPrimitiveTypeTriangleStrip;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline MTLResourceOptions
BufferUsageFlag(const Render::UsagePattern usage, const Render::ImmutableFlags flags)
{
    using namespace Render;
    MTLResourceOptions opts = 0;
    switch (usage)
    {
        case UsagePattern::CPUReadGPUWrite:
            opts |= MTLResourceCPUCacheModeWriteCombined;
        break;
        case UsagePattern::CPUWriteGPURead:
            opts |= MTLResourceCPUCacheModeWriteCombined;
        break;
        case UsagePattern::GPUReadGPUWrite:
            opts |= MTLResourceStorageModePrivate;
        break;
        case UsagePattern::Undefined:
            j_error("Metal::BufferUsageFlag(): Cannot leave buffer usage pattern unchanged");
        break;
    }
    
    switch (flags)
    {
        case ImmutableFlags::Coherent:
            j_assert_msg(opts & MTLStorageModePrivate, "Metal::BufferUsageFlag(): Cannot combine Coherent and GPUReadGPUWrite flags (since the buffer is GPU private).");
            opts |= MTLResourceStorageModeShared;
        break;
        case ImmutableFlags::Persistent:
            // hmm, do nothing, this is implicit with coherent buffers...
        break;
        case ImmutableFlags::DynamicStorage:
            // ignore, no such thing in Metal
        break;
        case ImmutableFlags::None:
            // this is also okay
        break;
    }
    return opts;
}

//------------------------------------------------------------------------------
/**
*/
inline MTLBlendOperation
BlendOpFlag(const Render::BlendState::BlendOp op)
{
    using namespace Render;
    switch (op)
    {
        case BlendState::BlendOp::Add:          return MTLBlendOperationAdd;
        case BlendState::BlendOp::Subtract:     return MTLBlendOperationSubtract;
        case BlendState::BlendOp::InvSubtract:  return MTLBlendOperationReverseSubtract;
        case BlendState::BlendOp::Min:          return MTLBlendOperationMin;
        case BlendState::BlendOp::Max:          return MTLBlendOperationMax;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline MTLBlendFactor
BlendModeFlag(const Render::BlendState::BlendMode mode)
{
    using namespace Render;
    switch (mode)
    {
        case BlendState::BlendMode::Zero:                       return MTLBlendFactorZero;
        case BlendState::BlendMode::One:                        return MTLBlendFactorOne;
        case BlendState::BlendMode::SourceColor:                return MTLBlendFactorSourceColor;
        case BlendState::BlendMode::OneMinusSourceColor:        return MTLBlendFactorOneMinusSourceColor;
        case BlendState::BlendMode::SourceAlpha:                return MTLBlendFactorSourceAlpha;
        case BlendState::BlendMode::OneMinusSourceAlpha:        return MTLBlendFactorOneMinusSourceAlpha;
        case BlendState::BlendMode::DestinationColor:           return MTLBlendFactorDestinationColor;
        case BlendState::BlendMode::OneMinusDestinationColor:   return MTLBlendFactorOneMinusDestinationColor;
        case BlendState::BlendMode::DestinationAlpha:           return MTLBlendFactorDestinationAlpha;
        case BlendState::BlendMode::OneMinusDestinationAlpha:   return MTLBlendFactorOneMinusDestinationAlpha;
        case BlendState::BlendMode::SourceAlphaSaturated:       return MTLBlendFactorSourceAlphaSaturated;
        case BlendState::BlendMode::BlendColor:                 return MTLBlendFactorBlendColor;
        case BlendState::BlendMode::OneMinusBlendColor:         return MTLBlendFactorOneMinusBlendColor;
        case BlendState::BlendMode::BlendAlpha:                 return MTLBlendFactorBlendAlpha;
        case BlendState::BlendMode::OneMinusBlendAlpha:         return MTLBlendFactorOneMinusBlendAlpha;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline MTLCompareFunction
CompareModeFlag(const Render::CompareMode mode)
{
    using namespace Render;
    switch (mode)
    {
        case CompareMode::Never:        return MTLCompareFunctionNever;
        case CompareMode::Less:         return MTLCompareFunctionLess;
        case CompareMode::Equal:        return MTLCompareFunctionEqual;
        case CompareMode::LessEqual:    return MTLCompareFunctionLessEqual;
        case CompareMode::Greater:      return MTLCompareFunctionGreater;
        case CompareMode::GreaterEqual: return MTLCompareFunctionGreaterEqual;
        case CompareMode::NotEqual:     return MTLCompareFunctionNotEqual;
        case CompareMode::Always:       return MTLCompareFunctionAlways;
    }
}

//------------------------------------------------------------------------------
/**
*/
inline MTLStencilOperation
StencilOpFlag(const Render::StencilOp op)
{
    using namespace Render;
    switch (op)
    {
        case StencilOp::Keep:           return MTLStencilOperationKeep;
        case StencilOp::Zero:           return MTLStencilOperationZero;
        case StencilOp::Replace:        return MTLStencilOperationReplace;
        case StencilOp::IncrementClamp: return MTLStencilOperationIncrementClamp;
        case StencilOp::DecrementClamp: return MTLStencilOperationDecrementClamp;
        case StencilOp::Invert:         return MTLStencilOperationInvert;
        case StencilOp::IncrementWrap:  return MTLStencilOperationIncrementWrap;
        case StencilOp::DecrementWrap:  return MTLStencilOperationDecrementWrap;
    }
}

}}} // namespace JARVIS::Metal::Types

#endif