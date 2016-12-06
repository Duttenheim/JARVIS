#pragma once
//------------------------------------------------------------------------------
/**
	@file core/debug.h

	Debug macros.

	(C) 2015 See the LICENSE file.
*/
#include <assert.h>
#include <string.h>
#include <cstdarg>

#if !__WIN32__
#include <stdio.h>
#endif

#define j_assert(exp) { if (!(exp)) JARVIS::Core::Debug::Exception(#exp, __FILE__, __LINE__); }
#define j_assert_msg(exp, msg) { if (!(exp)) JARVIS::Core::Debug::ExceptionWithMsg(#exp, msg, __FILE__, __LINE__); }
#define j_error(msg, ...) { JARVIS::Core::Debug::Error(msg, ##__VA_ARGS__); }

#ifdef __CONST_EXPR_SUPPORTED__
#define j_static_assert(exp, msg) static_assert(exp, msg)
#else
#define j_static_assert(exp, msg) j_assert_msg(exp, msg)
#endif

namespace JARVIS {
namespace Core {
namespace Debug 
{

//------------------------------------------------------------------------------
/**
*/
static void
Exception(const char* exp, const char* file, int line)
{
	const char* format = "JARVIS encountered an exception from which it cannot recover. \n\n Expression: \n    %s \ntriggered an abortion in:\n  file '%s'\n  line %d";
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

//------------------------------------------------------------------------------
/**
*/
static void
ExceptionWithMsg(const char* exp, const char* msg, const char* file, int line)
{
	const char* format = "JARVIS encountered an exception from which it cannot recover. \n\n Expression: \n    %s \ntriggered an abortion. Message: %s in:\n  file '%s'\n  line %d";
#if __WIN32__
	uint32 len = std::strlen(exp) + strlen(file) + strlen(format);
	char* buf = new char[len];
	sprintf_s(buf, len, format, exp, msg, file, line);
	::MessageBox(NULL, buf, "JARVIS NON-RECOVERABLE ERROR", MB_OK | MB_APPLMODAL | MB_SETFOREGROUND | MB_TOPMOST | MB_ICONERROR);
	delete[] buf;
#else
	printf(format, exp, file, line);
#endif
	abort();
}

//------------------------------------------------------------------------------
/**
*/
static void
Error(const char* fmt, ...)
{
    va_list arg;
    va_start(arg, fmt);
#if __WIN32__
	uint32 len = std::strlen(exp) + strlen(file) + strlen(format);
	char* buf = new char[len];
    char buf[2048];
    vsprintf(buf, fmt, arg);
	::MessageBox(NULL, buf, "JARVIS NON-RECOVERABLE ERROR", MB_OK | MB_APPLMODAL | MB_SETFOREGROUND | MB_TOPMOST | MB_ICONERROR);
	delete[] buf;
#else
	vprintf(fmt, arg);
#endif
    va_end(arg);
	abort();
}

}}} // namespace JARVIS::Core::Debug

