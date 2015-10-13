//------------------------------------------------------------------------------
/**
    @class JARVIS::Base::Buffer
 	(C) 2015 See the LICENSE file.
*/
#include "buffer.h"
namespace JARVIS {
namespace Base
{
    
//------------------------------------------------------------------------------
/**
*/
Buffer::Buffer() :
    storage(Render::StorageType::Initial)
{
    // empty
}

//------------------------------------------------------------------------------
/**
*/
Buffer::~Buffer()
{
    // empty
}

}} // namespace JARVIS::Base
