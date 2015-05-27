//------------------------------------------------------------------------------
/**
    @file core/config.h
    
	Main configure file for types and OS-specific stuff.
	
	(C) 2015 See the LICENSE file.
*/
#ifdef __WIN32__
#include "win32/pch.h"
#elif __APPLE__
#include "apple/pch.h"
#elif __UNIX__
#include "posix/pch.h"
#endif

#include <stdint.h>
#include <atomic>
#include <xmmintrin.h>

typedef uint32_t	uint32;
typedef int32_t		int32;
typedef uint16_t	uint16;
typedef int16_t		int16;
typedef uint8_t		uint8;
typedef int8_t		int8;
typedef uint8_t		uchar;

// eh, windows already defines byte, so don't redefine byte if we are running windows
#ifndef __WIN32__
typedef uint8_t      byte;
#endif

typedef uint8_t		ubyte;
typedef float		float32;
typedef double		float64;

// hmm, this is questionable, we actually want SSE vectors to operate as classes
typedef __m128		vec4;
typedef __m128i		ivec4;
typedef __m128d		dvec4;

// hmm, maybe move this to each platforms pch.h
#if __WIN32__
#define JARVIS_MAIN int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
#define JARVIS_MAIN int main(int argc, const char** argv)
#endif

#define j_min(x, y) x < y ? x : y
#define j_max(x, y) x > y ? x : y

#ifdef NULL
#undef NULL
#define NULL nullptr
#endif

#include "class.h"
#include "singleton.h"
#include "debug.h"
#include "ref.h"
#include "ptr.h"
#include "mem.h"
#include "enum.h"
