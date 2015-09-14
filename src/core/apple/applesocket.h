#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Apple::AppleSocket
	
    Implements a POSIX socket as implemented on Apple based platforms.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include <sys/socket.h>
namespace JARVIS {
namespace Apple
{
class AppleSocket
{
public:
    /// constructor
    AppleSocket();
    /// destructor
    virtual ~AppleSocket();
    
private:
};

}} // namespace JARVIS::Apple