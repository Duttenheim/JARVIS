#pragma once
//------------------------------------------------------------------------------
/**
	@file core/win32/pch.h

	Main configure file for types and Win32-specific stuff.

	(C) 2015 See the LICENSE file.
*/
#ifndef WIN32_LEAN_AND_MEAN
#define WIN32_LEAN_AND_MEAN
#endif

#define _WIN32_WINNT 0x0503

#define NOGDICAPMASKS
#define OEMRESOURCE
#define NOATOM
// clashes with shlobj.h
//#define NOCTLMGR
#define NOMEMMGR
#define NOMETAFILE
#define NOOPENFILE
#define NOSERVICE
#define NOSOUND
#define NOCOMM
#define NOKANJI
#define NOHELP
#define NOPROFILER
#define NODEFERWINDOWPOS
#define NOMCX

// Windows headers
#include <windows.h>
#include <winbase.h>
#include <process.h>
#include <shlobj.h>
#include <tchar.h>
#include <strsafe.h>
#include <wininet.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <rpc.h>
#include <dbghelp.h>
#include <intrin.h>