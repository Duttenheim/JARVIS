//------------------------------------------------------------------------------
/**
    @class JARVIS::Apple::Socket
 	(C) 2015 See the LICENSE file.
*/

#include "applesocket.h"
#include "network/socket.h"
#include "mem.h"
#include <poll.h>
#include <sys/ioctl.h>
#include <unistd.h>


using namespace JARVIS::Core;
namespace JARVIS {
namespace Apple
{
    
//------------------------------------------------------------------------------
/**
*/
Socket::Socket() :
    sock(0)
{
    Memory::Fill(&this->ip, sizeof(sockaddr), 0);
}

//------------------------------------------------------------------------------
/**
*/
Socket::~Socket()
{
    if (this->state == State::Connected) this->Close();
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Listen(const uint16 port)
{
	Interface::Socket::Listen(port);
	j_assert(this->sock == 0);

	Memory::Fill(&this->ip, sizeof(this->ip), 0);
    int family;
#ifdef JARVIS_USE_IPV6
	family = AF_INET6;
#else
	family = AF_INET;
#endif
    this->sock = socket(
        family,
        this->proto == Protocol::TCP ? SOCK_STREAM : SOCK_DGRAM,
        this->proto == Protocol::TCP ? IPPROTO_TCP : IPPROTO_UDP
    );
    j_assert(this->sock != -1);
    
    this->ip.sin_len = sizeof(this->ip);
    this->ip.sin_port = htons(port);
    this->ip.sin_family = family;
    this->ip.sin_addr.s_addr = INADDR_ANY;
    int stat = bind(this->sock, (sockaddr*)&this->ip, sizeof(this->ip));
    j_assert(stat >= 0);
    
    stat = listen(this->sock, SOMAXCONN);
    j_assert(stat >= 0);
}

//------------------------------------------------------------------------------
/**
*/
Ptr<Interface::Socket>
Socket::Accept()
{
    Ptr<Network::Socket> newSock = Network::Socket::Create();
    sockaddr_in addr;
    newSock->sock = accept(this->sock, (sockaddr*)&addr, nullptr);
    newSock->ip = addr;
    
    pollfd fd;
    fd.fd = this->sock;
    fd.events = POLLWRITE | POLLIN;
    int stat = poll(&fd, 1, 0);
    j_assert(stat >= 0);
    
    newSock->state = State::Connected;
    return newSock;
    //int stat = select(
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Send(const char *data, SizeT size)
{
    Interface::Socket::Send(data, size);
    int stat = send(this->sock, data, (int)size, 0);
    j_assert(stat >= 0);
}

//------------------------------------------------------------------------------
/**
*/
bool
Socket::PendingData()
{
    int count;
    ioctl(this->sock, FIONREAD, &count);
    return count > 0;
}

//------------------------------------------------------------------------------
/**
*/
SizeT
Socket::Receive(char* data, SizeT size)
{
    Interface::Socket::Receive(data, size);
    int stat = recv(this->sock, data, (int)size, 0);
    j_assert(stat >= 0);
    return stat;
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::Close()
{
    Interface::Socket::Close();
    
    j_assert(this->sock != 0);
    j_assert(shutdown(this->sock, SHUT_RDWR) >= 0);
    close(this->sock);
    this->state = State::Initial;
    this->sock = 0;
}

//------------------------------------------------------------------------------
/**
*/
void
Socket::__Connect()
{
    j_assert(this->sock == 0);

	Memory::Fill(&this->ip, sizeof(this->ip), 0);
    int family;
#ifdef JARVIS_USE_IPV6
	family = AF_INET6;
#else
	family = AF_INET;
#endif
    this->sock = socket(
        family,
        this->proto == Protocol::TCP ? SOCK_STREAM : SOCK_DGRAM,
        this->proto == Protocol::TCP ? IPPROTO_TCP : IPPROTO_UDP
    );
    j_assert(this->sock != -1);
    
    // resolve IP
    addrinfo* res = nullptr;
	//int stat = getaddrinfo(this->address.CharPtr(), this->port, &this->context, &res);
	//j_assert(stat == 0);
    this->context = *res;
    
    // connect socket
    this->ip.sin_port = htons(port);
    this->ip.sin_len = sizeof(this->ip);
    this->ip.sin_family = family;
    //this->ip.sin_addr.s_addr = this->context.
    //int stat = connect(this->sock, (sockaddr*)&this->ip, sizeof(sockaddr));
    //j_assert(stat >= 0);
}

}} // namespace JARVIS::Apple
