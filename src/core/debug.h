#pragma once
//------------------------------------------------------------------------------
/**
	@file core/debug.h

	Debug macros.

	(C) 2015 See the LICENSE file.
*/
#include <assert.h>
#include <string.h>

#if !__WIN32__
#include <stdio.h>
#endif

#define j_assert(exp) { if (!(exp)) JARVIS::Core::Debug::Error(#exp, __FILE__, __LINE__); }

namespace JARVIS {
namespace Core {
namespace Debug 
{

//------------------------------------------------------------------------------
/**
*/
static void
Error(const char* exp, const char* file, int line)
{
	const char* format = "JARVIS encountered an exception from which it cannot recover. \n\n Expression: \n    %s \ntriggered a breakpoint in:\n  file '%s'\n  line %d";
#if __WIN32__
	uint32 len = std::strlen(exp) + strlen(file) + strlen(format);
	char* buf = new char[len];
	sprintf_s(buf, len, format, exp, file, line);
	::MessageBox(NULL, buf, "JARVIS NON-RECOVERABLE ERROR", MB_OK | MB_APPLMODAL | MB_SETFOREGROUND | MB_TOPMOST | MB_ICONERROR);
	delete[] buf;
#else
	printf(format, exp, file, line);
#endif
	abort();
}

}}}

