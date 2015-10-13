#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::Texture
	
    Metal implementation of a texture.
	
	(C) 2015 See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "resources/texture.h"
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
    
private:
    friend class Metal::PipelineState;
    friend class Metal::RenderTarget;
    
    OBJC_ID_POINTER(MTLTexture) texture;
};

}} // namespace JARVIS::Metal