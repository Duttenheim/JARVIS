#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::Texture
	
    Metal implementation of a texture.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "resources/texture.h"
#include "types.h"
namespace JARVIS {
namespace Metal
{
class PipelineState;
class RenderTarget;
class Texture : public Base::Texture
{
    __ClassDecl(Texture);
public:
    
    /// constructor
    Texture();
    /// destructor
    virtual ~Texture();
    
    /// initialize as drawable
    void InitDrawable(TextureType type, Render::PixelFormat pixelFormat, uint32 width, uint32 height, uint8 mips = 1, uint8 samples = 1);
    /// initialize with data
    void InitWithData(TextureType type, Render::PixelFormat pixelFormat, uint32 width, uint32 height, byte* data, uint32 size, uint8 mips = 1);
    
private:
    friend class Metal::PipelineState;
    friend class Metal::RenderTarget;
    
    OBJC_ID_POINTER(MTLBuffer) textureBuffer;
    OBJC_ID_POINTER(MTLTexture) texture;
};

}} // namespace JARVIS::Metal