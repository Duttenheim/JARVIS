#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Metal::Context
	
    Implements a metal context.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "types.h"
namespace JARVIS {
namespace Metal
{
class Context
{
public:
    /// constructor
    Context();
    /// destructor
    virtual ~Context();
    
    /// setup context
    void Setup();
    
private:
    OBJC_ID_POINTER(MTLDevice) device;
};

}} // namespace JARVIS::Metal