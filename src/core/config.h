#pragma once
//------------------------------------------------------------------------------
//  @file core/config.h
//    
//	Main configure file for types and generic OS-specific stuff.
//	
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------
#ifdef __WIN32__
#include "win32/pch.h"
#elif __APPLE__
#include "apple/pch.h"
#elif __UNIX__
#include "posix/pch.h"
#endif

#ifdef __cplusplus
#include <stdlib.h>
#include <stdint.h>
#include <atomic>
#include <utility>
#include <xmmintrin.h>
#include <smmintrin.h>
#include <initializer_list>
#include <limits.h>
#include <float.h>

typedef uint64_t    uint64;
typedef int64_t     int64;
typedef uint32_t	uint32;
typedef int32_t		int32;
typedef uint16_t	uint16;
typedef int16_t		int16;
typedef uint8_t		uint8;
typedef int8_t		int8;
typedef uint8_t		uchar;
typedef ptrdiff_t	ptrdiff;
typedef size_t		SizeT;
typedef ptrdiff_t	IndexT;

// eh, windows already defines byte, so don't redefine byte if we are running windows
#ifndef __WIN32__
typedef int8_t      byte;
#endif

typedef uint8_t		ubyte;
typedef float		float32;
typedef double		float64;

// hmm, this is questionable, we actually want SSE vectors to operate as classes
typedef __m128		vec4;
typedef __m128i		ivec4;
typedef __m128d		dvec4;

// typedef away ugly std:::initializer_list syntax
// danger: using in clang as const ref causes corruption
template <class T>
using InitList = std::initializer_list<T>;

// typedef std::array<T, N> so it becomes clear it's a constant array
template <class TYPE, uint32 N>
using ConstArr = std::array<TYPE, N>;

template <class... TYPE>
using Tuple = std::tuple<TYPE...>;

#if __WIN32__
#define align_16 __declspec(align(16))
#pragma warning (disable : 4996)	// CRT secure warning
#elif __APPLE__ || __UNIX__
#define align_16 __attribute__((aligned(16))) __attribute((packed))
#else
#endif

// hmm, maybe move this to each platforms pch.h
#if __WIN32__
    #define JARVIS_MAIN  using namespace JARVIS; \
    int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance, LPSTR lpCmdLine, int nShowCmd)
#else
    #define JARVIS_MAIN using namespace JARVIS; \
    int main(int argc, const char** argv)
#endif

// check for maximum opengl version, only restricted on OS X
#if __APPLE__
#define OPENGL_VERSION_MAX 41
#else
#define OPENGL_VERSION_MAX INT_MAX
#endif

#define j_min(x, y) x < y ? x : y
#define j_max(x, y) x > y ? x : y
//#define j_assert(exp) { printf("JARVIS assertion failed: %s", #exp); exit(EXIT_FAILURE); }
//#define j_assert_msg(exp, msg) { printf("JARVIS assertion failed: %s. Message: %s", #exp, msg); exit(EXIT_FAILURE); }

#ifdef NULL
#undef NULL
#define NULL nullptr
#endif

#if J_RENDERER_GL4
#include <glew.h>
#endif

#include "debug.h"
#include "mem.h"
#include "constness.h"
#include "singleton.h"
#include "ref.h"
#include "ptr.h"
#include "enum.h"
#include "poolalloc.h"
#include "class.h"

namespace JARVIS {

// define shorthand aliases for common types
template <class TYPE>
using Array = Core::Array<TYPE>;
using String = Core::String;
using Ref = Core::Ref;

}
#endif