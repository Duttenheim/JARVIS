#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Core::Socket
	
    Basic TCP/IP socket. Depending on the platform, actually implemented by the socket method 
    supported by the operating system.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "util/string.h"
#include "util/array.h"
namespace JARVIS {
namespace Core
{
class Socket : public Ref
{
public:

    enum SocketState
    {
        Initial,
        Connected,
        Disconnected
    };
    
    /// constructor
    Socket();
    /// destructor
    virtual ~Socket();
    
    /// connect socket to address
    void Connect(const String& address, const uint32 port);
    /// disconnect, assumes socket is connected already
    void Disconect();
    
    /// send data through socket
    void Send(byte* bytes, uint32 size);
    /// send data through socket using byte array
    void Send(const Array<byte*>& data);
    
private:
    SocketState state;
};

}} // namespace JARVIS::Core