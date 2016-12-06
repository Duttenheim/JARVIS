//------------------------------------------------------------------------------
/**
    @class JARVIS::Base::Context
 	(C) 2015 See the LICENSE file.
*/
#include "context.h"
#include "../context.h"
namespace JARVIS {
namespace Base
{
    
Ptr<Render::Context> Context::Current = nullptr;
//------------------------------------------------------------------------------
/**
*/
Context::Context()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Context::~Context()
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
bool
Context::Setup()
{
    return false;
}

//------------------------------------------------------------------------------
/**
*/
void
Context::Discard()
{

}

//------------------------------------------------------------------------------
/**
*/
void
Context::MakeCurrent()
{
    Context::Current = this;
}

//------------------------------------------------------------------------------
/**
*/
Ptr<Render::Shader>
Context::LoadShader(const Core::String& name)
{
    const uint32 hash = name.Hash();
    if (this->shaders.Contains(hash)) return this->shaders.Value(hash);
    else
    {
        Ptr<Render::Shader> shader = Render::Shader::Create();
        shader->Load(name);
        this->shaders.Insert(hash, shader);
        return shader;
    }
}

//------------------------------------------------------------------------------
/**
*/
void
Context::Draw()
{

}

//------------------------------------------------------------------------------
/**
*/
void
Context::Draw(uint32 numInstances)
{

}


}} // namespace JARVIS::Core
