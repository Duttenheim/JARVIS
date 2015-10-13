#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Base::ShaderState
	
    A shader state contains a localized shader state, 
    which is a shader object and its uniform values.
    
    Applying this object to the context will cause:
     The shader to be bound.
     Uniform values will be applied.
     Uniform buffers will be bound.
     Storage buffers will be bound.
     Textures will be bound.
     Read/write images will be bound.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Base
{
class ShaderState : public Core::Ref
{
    __ClassDecl(ShaderState);
public:
    /// constructor
    ShaderState();
    /// destructor
    virtual ~ShaderState();
    
private:
};

}} // namespace JARVIS::Base