//------------------------------------------------------------------------------
//  @class JARVIS::Core::Socket
// 	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------
#include "config.h"
#include "socket.h"
namespace JARVIS {
namespace Interface
{
//------------------------------------------------------------------------------
/**
*/
Socket::Socket() :
	state(SocketState::Initial),
	proto(Protocol::TCP)
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
Socket::~Socket()
{
	// empty, but a good idea is to call Close() in the subclasses if the socket is connected
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Listen(const String& port)
{
	j_assert(this->state == SocketState::Initial);
	this->state = SocketState::Listening;
	this->port = port;
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Connect(const String& address)
{
	j_assert(this->state == SocketState::Initial);
	Array<String> fragments = address.Split(":");
	j_assert_msg(fragments.Size() > 0, "Socket address must contain trailing :<port>");
	this->address = fragments[0];
	this->port = fragments[1];

	// open socket
	this->__Connect();
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Connect(const String& address, const String& port)
{
	j_assert(this->state == SocketState::Initial);
	this->address = address;
	this->port = port;

	// open socket
	this->__Connect();
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Close()
{
	this->state = SocketState::Initial;
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Send(const char* data, SizeT size)
{
	j_assert(this->state == SocketState::Connected);
}

//------------------------------------------------------------------------------
/**
*/
SizeT
Socket::Receive(char* data, SizeT size)
{
	j_assert(this->state == SocketState::Connected);
	return 0;
}

//------------------------------------------------------------------------------
/**
*/
bool
Socket::PendingData()
{
	j_assert(this->state == SocketState::Connected);
	return false;
}

}} // namespace JARVIS::Interface
