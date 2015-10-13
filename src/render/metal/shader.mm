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
    Base::Shader::Load(Core::Forward(name));
    this->shader = [Context::Current->library newFunctionWithName:[[NSString alloc] initWithCString: name.CharPtr() encoding:NSUnicodeStringEncoding]];
}

}} // namespace JARVIS::Metal
