#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Base::Texture
	
    Base implementation of a texture.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/pixeltypes.h"
namespace JARVIS {
namespace Base
{

class Texture : public Core::Ref
{
    __ClassDecl(Texture)
public:
    
    enum class TextureType : uint8
    {
        Texture2D,
        Texture3D,
        TextureCube,
        Texture2DArray,
        Texture3DArray,
        TextureCubeArray
    };

    /// constructor
    Texture();
    /// destructor
    virtual ~Texture();
    
    /// initialize as drawable
    void InitDrawable(TextureType type, Render::PixelFormat pixelFormat, uint32 width, uint32 height, uint8 mips = 1, uint8 samples = 1);
    /// initialize with data
    void InitWithData(TextureType type, Render::PixelFormat pixelFormat, uint32 width, uint32 height, byte* data, uint32 size, uint8 mips = 1);
    
    /// generate mipmaps
    void GenerateMips();
    
protected:
    TextureType type;
    Render::PixelFormat pixelFormat;
    uint32 width, height;
    uint8 mips;
    uint8 samples;
};

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::InitDrawable(Texture::TextureType type, Render::PixelFormat pixelFormat, uint32 width, uint32 height, uint8 mips, uint8 samples)
{
    this->type = type;
    this->pixelFormat = pixelFormat;
    this->width = width;
    this->height = height;
    this->mips = mips;
    this->samples = samples;
}

//------------------------------------------------------------------------------
/**
*/
inline void
Texture::InitWithData(Texture::TextureType type, Render::PixelFormat pixelFormat, uint32 width, uint32 height, byte *data, uint32 size, uint8 mips)
{
    this->type = type;
    this->pixelFormat = pixelFormat;
    this->width = width;
    this->height = height;
    this->mips = mips;
    this->samples = 1;
}

}} // namespace JARVIS::Base