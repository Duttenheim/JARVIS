#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Apple::AppleSocket
	
    Implements a POSIX socket as on Apple based platforms.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "util/string.h"
#include <sys/socket.h>
#include <sys/types.h>
namespace JARVIS {
namespace Apple
{
class Socket
{
public:
    /// constructor
    Socket();
    /// destructor
    virtual ~Socket();
    
    /// open socket on address and port
    void Open();
    /// close socket, asserts it is open already
    void Close();
    /// returns true if socket is open
    bool IsOpen() const;
    
    /// connects socket to address and port
    void Connect(const Core::String& addr, const uint16 port);
    /// disconnects socket, which makes it connectable again
    void Disconnect();
    /// returns true if socket is connected
    bool IsConnected() const;
    
private:
    bool open;
    bool connected;
    sockaddr ip;
    int32 socket;
};

//------------------------------------------------------------------------------
/**
*/
inline bool
Socket::IsOpen() const
{
    return this->open;
}

//------------------------------------------------------------------------------
/**
*/
inline bool
Socket::IsConnected() const
{
    return this->connected;
}

}} // namespace JARVIS::Apple