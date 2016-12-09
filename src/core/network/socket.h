#pragma once
//------------------------------------------------------------------------------
/**
	@class JARVIS::Network::SysFunc

	Wraps the OS-specific socket implementation.

	(C) 2016 See the LICENSE file.
*/
//------------------------------------------------------------------------------

#if __WIN32__
#include "win32/win32socket.h"
__Wrap(Network, Win32, Socket);
#elif __APPLE__
#include "apple/applesocket.h"
__Wrap(Network, Apple, Socket);
#elif __LINUX__
#include "posix/posixsocket.h"
__Wrap(Network, Posix, Socket);
#endif