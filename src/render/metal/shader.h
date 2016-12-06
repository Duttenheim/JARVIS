#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Render::Shader
	
    Metal implementation of a shader.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "shading/shader.h"
namespace JARVIS {
namespace Metal
{
class PipelineState;
class Context;
class Shader : public Base::Shader
{
    __ClassDecl(Shader);
public:
    /// constructor
    Shader();
    /// destructor
    virtual ~Shader();
    
    /// load shader
    void Load(const Core::String& name);
    
private:
    friend class Metal::Context;
    friend class Metal::PipelineState;
    OBJC_ID_POINTER(MTLFunction) shader;
};

}} // namespace JARVIS::Metal