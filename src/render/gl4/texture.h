#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::Texture
	
    Implements a texture as used in OpenGL
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "resources/texture.h"
namespace JARVIS {
namespace GL4
{
class RenderTarget;
class Texture : public Base::Texture
{
public:
    /// constructor
    Texture();
    /// destructor
    virtual ~Texture();
    
private:
    friend class GL4::RenderTarget;
    GLuint handle;
};

}} // namespace JARVIS::GL4