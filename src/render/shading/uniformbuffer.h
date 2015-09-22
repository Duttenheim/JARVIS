#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::UniformBuffer
	
    Interface level uniform buffer (for uniform shader data)
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Render
{
class UniformBuffer
{
public:
    /// constructor
    UniformBuffer();
    /// destructor
    virtual ~UniformBuffer();
    
private:
};

}} // namespace JARVIS::Render