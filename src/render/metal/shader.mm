//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::Shader
 	(C) 2015 See the LICENSE file.
*/
#include "shader.h"
#include "../context.h"
namespace JARVIS {
namespace Metal
{
    
//------------------------------------------------------------------------------
/**
*/
Shader::Shader()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Shader::~Shader()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
void
Shader::Load(const Core::String& name)
{
    Base::Shader::Load(Fw(name));
    NSString* shaderName = [[NSString alloc] initWithCString: name.CharPtr() encoding:NSUTF8StringEncoding];
    this->shader = [Context::Current->library newFunctionWithName:shaderName];
}

}} // namespace JARVIS::Metal
