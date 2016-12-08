//------------------------------------------------------------------------------
// @class	JARVIS::Win32::Socket
// @file	win32socket.cc
// (C) 2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "pch.h"
#include "win32socket.h"
#include "mem.h"


using namespace JARVIS::Core;
namespace JARVIS {
namespace Win32
{

//------------------------------------------------------------------------------
/**
*/
Socket::Socket() :
	sock(0),
	proto(Protocol::TCP)
{
	Memory::Fill(&this->context, sizeof(this->context), 0);
}

//------------------------------------------------------------------------------
/**
*/
Socket::Socket(const Socket& socket)
{
	Memory::Fill(&this->context, sizeof(this->context), 0);
	this->sock = socket.sock;
	this->proto = socket.proto;
}

//------------------------------------------------------------------------------
/**
*/
Socket::Socket(Socket&& socket)
{
	Memory::Fill(&this->context, sizeof(this->context), 0);
	this->sock = socket.sock;
	this->proto = socket.proto;
	socket.sock = 0;
	socket.proto = Protocol::UnknownProtocol;
}

//------------------------------------------------------------------------------
/**
*/
Socket::~Socket()
{
	// empty
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Listen(const String& port)
{
	j_assert(this->sock == 0);
	Memory::Fill(&this->context, sizeof(this->context), 0);
#ifdef JARVIS_USE_IPV6
	this->context.ai_family = AF_INET6;
#else
	this->context.ai_family = AF_INET;
#endif
	this->context.ai_socktype = this->proto == Protocol::TCP ? SOCK_STREAM : SOCK_DGRAM;
	this->context.ai_protocol = this->proto == Protocol::TCP ? IPPROTO_TCP : IPPROTO_UDP;
	this->context.ai_flags = AI_PASSIVE;

	// convert port to string
	this->address = "localhost";
	this->port = port;
	j_assert(this->port.Length() < 6);
	addrinfo* res = nullptr;

	// resolve IP
	int stat = getaddrinfo(NULL, this->port.CharPtr(), &this->context, &res);
	j_assert(stat == 0);
	this->context = *res;

	// create socket
	this->sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	j_assert(this->sock != INVALID_SOCKET);

	// bind socket to port
	stat = bind(this->sock, res->ai_addr, (int)res->ai_addrlen);
	j_assert(stat != SOCKET_ERROR);
	freeaddrinfo(res);

	// start listening
	stat = listen(this->sock, SOMAXCONN);
	j_assert(stat != SOCKET_ERROR);
	
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Connect(const String& address)
{
	Array<String> fragments = address.Split(":");
	j_assert_msg(fragments.Size() > 0, "Socket address must contain trailing :<port>");
	this->address = fragments[0];
	this->port = fragments[1];

	// open socket
	this->Connect();
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Connect(const String& address, const String& port)
{
	this->address = address;
	this->port = port;

	// open socket
	this->Connect();
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Connect()
{
	j_assert(this->sock == 0);
	Memory::Fill(&this->context, sizeof(this->context), 0);
	this->context.ai_family = AF_UNSPEC;				// keep it unspec seeing as we might connect with ipv6
	this->context.ai_socktype = this->proto == Protocol::TCP ? SOCK_STREAM : SOCK_DGRAM;
	this->context.ai_protocol = this->proto == Protocol::TCP ? IPPROTO_TCP : IPPROTO_UDP;

	// convert port to string
	j_assert(this->port.Length() < 6);
	addrinfo* res = nullptr;

	// resolve IP
	int stat = getaddrinfo(this->address.CharPtr(), this->port.CharPtr(), &this->context, &res);
	j_assert(stat == 0);
	this->context = *res;

	// create socket
	this->sock = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
	j_assert(this->sock != INVALID_SOCKET);

	// connect socket
	stat = connect(this->sock, res->ai_addr, (int)res->ai_addrlen);
	j_assert(stat != SOCKET_ERROR);
	freeaddrinfo(res);
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Close()
{
	j_assert(this->sock != 0);
	j_assert(shutdown(this->sock, SD_SEND) != SOCKET_ERROR);
	closesocket(this->sock);
	this->sock = 0;
}

//------------------------------------------------------------------------------
/**
*/
Socket
Socket::Accept()
{
	Socket newSock;
	newSock.sock = accept(this->sock, NULL, NULL);
	return newSock;
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Send(const char* data, SizeT size)
{
	int stat = send(this->sock, data, (int)size, 0);
	j_assert(stat != SOCKET_ERROR);
}

//------------------------------------------------------------------------------
/**
*/
SizeT
Socket::Receive(char* data, SizeT size)
{
	int stat = recv(this->sock, data, (int)size, 0);
	j_assert(stat != SOCKET_ERROR);
	return stat;
}

//------------------------------------------------------------------------------
/**
*/
bool
Socket::PendingData()
{
	fd_set set;
	set.fd_array[0] = this->sock;
	set.fd_count = 1;
	timeval timeout = { 0, 0 };
	int res = select(0, &set, nullptr, nullptr, &timeout) == 1;
	j_assert(res != SOCKET_ERROR);
	return res != 0;
}

}} // namespace JARVIS::Win32