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
	state(State::Initial),
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
Socket::Listen(const uint16 port)
{
	j_assert(this->state == State::Initial);
	this->state = State::Listening;
	this->port = port;
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Connect(const Core::String& address)
{
	j_assert(this->state == State::Initial);
	Array<Core::String> fragments = address.Split(":");
	j_assert_msg(fragments.Size() > 0, "Socket address must contain trailing :<port>");
	this->address = fragments[0];
	this->port = atoi(fragments[1].CharPtr());

	// open socket
	this->__Connect();
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Connect(const Core::String& address, const uint16 port)
{
	j_assert(this->state == State::Initial);
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
	this->state = State::Initial;
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Send(const char* data, SizeT size)
{
	j_assert(this->state == State::Connected);
}

//------------------------------------------------------------------------------
/**
*/
SizeT
Socket::Receive(char* data, SizeT size)
{
	j_assert(this->state == State::Connected);
	return 0;
}

//------------------------------------------------------------------------------
/**
*/
bool
Socket::PendingData()
{
	j_assert(this->state == State::Connected);
	return false;
}

}} // namespace JARVIS::Interface
