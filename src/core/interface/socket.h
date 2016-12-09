#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Interface::Socket
	
    Interface class for sockets, inherit this class to implement OS-specific sockets
	
	(C) 2015 See the LICENSE file.
 */
//------------------------------------------------------------------------------
#include "util/string.h"
#include "util/array.h"
namespace JARVIS {
namespace Interface
{
class Socket : public Ref
{
	__ClassDecl(Socket);
public:

	enum class Protocol : uint8_t
	{
		UnknownProtocol,
		TCP,
		UDP
	};

    enum class SocketState : uint8_t
    {
        Initial,
        Connected,			// client is connected
        Disconnected,		// client is disconnected
		Listening			// server is listening
    };
    
	/// constructor
	Socket();
	/// destructor
	virtual ~Socket();

	/// setup as listening device (server)
	void Listen(const String& port);
	/// setup as connecting socket, port must be a part of address
	void Connect(const String& address);
	/// setup as connecting socket, port must be a part of address
	void Connect(const String& address, const String& port);

	/// block the application and accept a new connection
	virtual Ptr<Interface::Socket> Accept() = 0;

	/// send data on socket
	virtual void Send(const char* data, SizeT size);

	/// returns true if any data is pending
	bool PendingData();
	/// receive data on socket
	virtual SizeT Receive(char* data, SizeT size);

	/// close the connection
	virtual void Close();
    
protected:
	/// actually connect
	virtual void __Connect() = 0;

	String port;
	String address;
    SocketState state;
	Protocol proto;
};

}} // namespace JARVIS::Core