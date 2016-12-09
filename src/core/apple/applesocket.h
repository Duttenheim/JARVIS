#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Apple::AppleSocket
	
    Implements a POSIX socket as on Apple based platforms.
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "util/string.h"
#include "interface/socket.h"
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
namespace JARVIS {
namespace Apple
{
class Socket : public Interface::Socket
{
    __ClassDecl(Socket);
public:
    /// constructor
    Socket();
    /// destructor
    virtual ~Socket();
    
    /// setup socket as listener
    void Listen(const uint16 port);
    
    /// accept new connection
    Ptr<Interface::Socket> Accept();
    
    /// send data on socket
    void Send(const char* data, SizeT size);
    /// check if any pending data is available
    bool PendingData();
    /// receive data, returns number of bytes actually read
    SizeT Receive(char* data, SizeT size);
    
    /// close the connection
    void Close();
    
private:
    /// connect socket internally
    void __Connect();
    
    sockaddr_in ip;
    int32 sock;
};

}} // namespace JARVIS::Apple