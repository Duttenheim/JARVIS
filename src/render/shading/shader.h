#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::Shader
	
    Interface level shader object.
 
    A shader object is more than just a single pipeline stage, but encompasses an entire shader pipeline.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
namespace JARVIS {
namespace Render
{
class Shader
{
public:
    /// constructor
    Shader();
    /// destructor
    virtual ~Shader();
    
private:
};

}} // namespace JARVIS::Render