#pragma once
//------------------------------------------------------------------------------
/**
    @file core/config.h
    
	Main configure file for types and OS-specific stuff.
	
	(C) 2015 See the LICENSE file.
*/
#ifdef __WIN32__
#include "win32/pch.h"
#endif

#include <stdint.h>
#include <atomic>

typedef uint32_t	uint32;
typedef int32_t		int32;
typedef uint16_t	uint16;
typedef int16_t		int16;
typedef uint8_t		uint8;
typedef int8_t		int8;
typedef uint8_t		uchar;
typedef uint8_t		ubyte;
typedef float		float32;
typedef double		float64;
typedef __m128		vec4;
typedef __m128i		ivec4;
typedef __m128d		dvec4;

#define j_min(x, y) x < y ? x : y
#define j_max(x, y) x > y ? x : y

#ifdef NULL
#undef NULL
#define NULL nullptr
#endif

#include "class.h"
#include "singleton.h"
#include "debug.h"
