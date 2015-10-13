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
    
    /// generate mipmaps
    void GenerateMips();
    
protected:
    TextureType type;
    Render::PixelFormat pixelFormat;
    uint32 width, height;
    uint8 mips;
};

}} // namespace JARVIS::Base