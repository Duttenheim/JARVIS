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
namespace Base
{
class Shader : public Core::Ref
{
    __ClassDecl(Shader);
public:
    /// constructor
    Shader();
    /// destructor
    virtual ~Shader();
    
    /// load shader from name
    void Load(const Core::String& name);
    
private:
    Core::String name;
};

//------------------------------------------------------------------------------
/**
*/
inline void
Shader::Load(const Core::String &name)
{
    this->name = name;
}

}} // namespace JARVIS::Render