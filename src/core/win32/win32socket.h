#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Win32::Socket
	
	Implements a WINSOCK interface.
	
	(C) 2016  See the LICENSE file.
*/
//------------------------------------------------------------------------------
#include "ref.h"
namespace JARVIS {
namespace Core 
{
	class Socket;
}
namespace Win32
{
class Socket : public Core::Ref
{
	__ClassDecl(Socket);
public:

	enum class Protocol : uint8_t
	{
		UnknownProtocol,
		TCP,
		UDP
	};

	/// constructor
	Socket();
	/// copy constructor
	Socket(const Socket& socket);
	/// move constructor
	Socket(Socket&& socket);
	/// destructor
	virtual ~Socket();

	/// setup as listening device (server)
	void Listen(const String& port);
	/// setup as connecting socket, port must be a part of address
	void Connect(const String& address);
	/// setup as connecting socket, port must be a part of address
	void Connect(const String& address, const String& port);

	/// block the application and accept a new connection
	Socket Accept();

	/// send data on socket
	void Send(const char* data, SizeT size);

	/// returns true if any data is pending
	bool PendingData();
	/// receive data on socket
	SizeT Receive(char* data, SizeT size);

	/// close the connection
	void Close();
private:
	/// actually connect
	void Connect();
	SOCKET sock;
	addrinfo context;

	String port;
	String address;
	Protocol proto;

};
}} // namespace JARVIS::Win32