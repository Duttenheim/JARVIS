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
	__ClassDeclAbstract(Socket);
public:

	enum class Protocol : uint8_t
	{
		UnknownProtocol,
		TCP,
		UDP
	};

    enum class State : uint8_t
    {
        Initial,
        Connected,			// client is connected
        Disconnected,		// client is disconnected
		Listening			// server is listening
    };

	enum class Error : uint8_t
	{
		ConnectionRefused,
		ConnectionClosed,
		ReadFailed,
		WriteFailed
	};
    
	/// constructor
	Socket();
	/// destructor
	virtual ~Socket();

	/// setup as listening device (server)
	void Listen(const uint16 port);
	/// setup as connecting socket, port must be a part of address
	void Connect(const Core::String& address);
	/// setup as connecting socket, port must be a part of address
	void Connect(const Core::String& address, const uint16 port);

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

	uint16 port;
	Core::String address;
    State state;
	Protocol proto;
};

}} // namespace JARVIS::Core