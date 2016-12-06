//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::Texture
 	(C) 2015 See the LICENSE file.
*/
#include "texture.h"
#include "types.h"
#include "resources/buffertypes.h"

#include "../context.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
Texture::Texture()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Texture::~Texture()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::InitDrawable(Texture::TextureType type, Render::PixelFormat pixelFormat, uint32 width, uint32 height, uint8 mips, uint8 samples)
{
    Base::Texture::InitDrawable(type, pixelFormat, width, height, mips, samples);
    uint32 size = width * height * PixelSize(pixelFormat);
    MTLResourceOptions options = Types::BufferUsageFlag(Render::UsagePattern::GPUReadGPUWrite, Render::ImmutableFlags::None);
    this->textureBuffer = [Render::Context::Current->device newBufferWithLength:size options:options];
    
    // setup texture view
    MTLTextureDescriptor* desc = nil;
    if (type == Texture::TextureType::Texture2D)
    {
        desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:Types::PixelFormatFlag(pixelFormat) width:width height:height mipmapped:mips > 1];
    }
    else if (type == Texture::TextureType::TextureCube)
    {
        j_assert(width == height);
        desc = [MTLTextureDescriptor textureCubeDescriptorWithPixelFormat:Types::PixelFormatFlag(pixelFormat) size:width mipmapped:mips > 1];
    }
    else
    {
        j_error("Texture type %d is not supported by Metal!\n", type);
    }
    this->texture = [Render::Context::Current->device newTextureWithDescriptor:desc];

}

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::InitWithData(Texture::TextureType type, Render::PixelFormat pixelFormat, uint32 width, uint32 height, byte *data, uint32 size, uint8 mips)
{
    Base::Texture::InitWithData(type, pixelFormat, width, height, data, size, mips);
    MTLResourceOptions options = Types::BufferUsageFlag(Render::UsagePattern::CPUWriteGPURead, Render::ImmutableFlags::None);
    this->textureBuffer = [Render::Context::Current->device newBufferWithBytes:data length:size options:options];
    
    // setup texture view
    MTLTextureDescriptor* desc = nil;
    if (type == Texture::TextureType::Texture2D)
    {
        desc = [MTLTextureDescriptor texture2DDescriptorWithPixelFormat:Types::PixelFormatFlag(pixelFormat) width:width height:height mipmapped:mips > 1];
    }
    else if (type == Texture::TextureType::TextureCube)
    {
        j_assert(width == height);
        desc = [MTLTextureDescriptor textureCubeDescriptorWithPixelFormat:Types::PixelFormatFlag(pixelFormat) size:width mipmapped:mips > 1];
    }
    else
    {
        j_error("Texture type %d is not supported by Metal!\n", type);
    }
    this->texture = [Render::Context::Current->device newTextureWithDescriptor:desc];
}

}} // namespace Metal::Texture
