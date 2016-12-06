#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::GL4::Shader
	
    Implements a shader pipeline, which in OpenGL is called a program object.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "shading/shader.h"
namespace JARVIS {
namespace GL4
{
class Shader : public Base::Shader
{
    __ClassDecl(Shader);
public:
    /// constructor
    Shader();
    /// destructor
    virtual ~Shader();
    
private:
};

}} // namespace JARVIS::GL4