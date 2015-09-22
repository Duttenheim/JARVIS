//------------------------------------------------------------------------------
/**
    @class JARVIS::Metal::Context
 	(C) 2015 See the LICENSE file.
*/
#include "context.h"
namespace JARVIS {
namespace Metal
{
    
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
void
Context::Setup()
{
    this->device = MTLCreateSystemDefaultDevice();
}

}}
