#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::UniformBuffer
	
    Interface level uniform buffer (for uniform shader data).
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Base
{
class UniformBuffer : public Core::Ref
{
    __ClassDecl(UniformBuffer);
public:
    /// constructor
    UniformBuffer();
    /// destructor
    virtual ~UniformBuffer();
    
private:
};

}} // namespace JARVIS::Render