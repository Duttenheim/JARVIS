//------------------------------------------------------------------------------
// @class	JARVIS::Win32::SysFunc
// @file	sysfunc.cc
// (C) 2016 Individual contributors, see AUTHORS file
//------------------------------------------------------------------------------
#include "config.h"
#include "win32sysfunc.h"

namespace JARVIS {
namespace Win32
{

int SysFunc::WSAStatus = 0;
LPWSADATA SysFunc::WSAData;
//------------------------------------------------------------------------------
/**
*/
SysFunc::SysFunc()
{
	// setup WSA if not already
	if (SysFunc::WSAStatus == 0)
	{
		SysFunc::WSAData = new WSADATA;
		SysFunc::WSAStatus = WSAStartup(MAKEWORD(2, 2), SysFunc::WSAData);
		j_assert(SysFunc::WSAStatus == 0);
	}
}

//------------------------------------------------------------------------------
/**
*/
SysFunc::~SysFunc()
{
	WSACleanup();
	delete SysFunc::WSAData;
}

#define MAXPATHLEN 1024
//------------------------------------------------------------------------------
/**
*/
Core::String
SysFunc::BinDir()
{
	uint16 buf[MAXPATHLEN];
	DWORD res = GetModuleFileNameW(NULL, (LPWSTR)buf, sizeof(buf) / 2);
	j_assert(res != 0);

	char path[MAXPATHLEN];
	int numBytesConverted = WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)&res, -1, path, sizeof(path), 0, 0);
	j_assert(numBytesConverted > 0);

	// create string from converted buffer
	Core::String ret(path, numBytesConverted);
	ret.Replace('\\', '/');
	ret = ret.ExtractToEndFromLast('/');
	String home = ret.ExtractToIndex(ret.FindLast('/') + 1);
	return String("file:///") + home;
}

}} // namespace JARVIS::Win32