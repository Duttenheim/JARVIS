#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Win32::Socket
	
	Implements a WINSOCK interface.
	
	(C) 2016  See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "ref.h"
#include "interface/socket.h"
namespace JARVIS {
namespace Win32
{
class Socket : public Interface::Socket
{
	__ClassDecl(Socket);
public:

	/// constructor
	Socket();
	/// destructor
	virtual ~Socket();

	/// setup as listening device (server)
	void Listen(const uint16 port);

	/// block the application and accept a new connection
	Ptr<Interface::Socket> Accept();

	/// send data on socket
	void Send(const char* data, SizeT size);

	/// returns true if any data is pending
	bool PendingData();
	/// receive data on socket
	SizeT Receive(char* data, SizeT size);

	/// close the connection
	void Close();
protected:
	/// connect the WinSock
	void __Connect();
	SOCKET sock;
	addrinfo context;

};
}} // namespace JARVIS::Win32