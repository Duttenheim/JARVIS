#pragma once
//------------------------------------------------------------------------------
/**
	@file core/enum.h

	Macros useful for managing enums. Instant if constexpr is available.

	(C) 2015 See the LICENSE file.
*/
#include <string.h>

#if __CONST_EXPR_SUPPORTED__
#define __SWITCHSTRING(x) switch (__StringHash(x))
#define __FROMSTRING(x) case __StringHash(#x) : return x;
#define __DEFAULT(x) default: return x;
#define __TOSTRING(x) case x : return #x;
#else
#define __SWITCHSTRING(x) auto __switch_str = x;
#define __FROMSTRING(x) if (0 == strcmp(#x, __switch_str)) return x;
#define __DEFAULT(x) return x;
#define __TOSTRING(x) case x : return #x;
#endif

#define __ENUM_OR_OPERATOR(x) \
    inline friend x operator|(x lhs, x rhs) \
    { \
        return static_cast<x>(static_cast<int32>(lhs) | static_cast<int32>(rhs)); \
    } \
    inline friend void operator|=(x lhs, x rhs) \
    { \
        lhs = static_cast<x>(static_cast<int32>(lhs) | static_cast<int32>(rhs)); \
    }

#define __ENUM_AND_OPERATOR(x) \
    inline friend x operator&(x lhs, x rhs) \
    { \
        return static_cast<x>(static_cast<int32>(lhs) & static_cast<int32>(rhs)); \
    } \
    inline friend void operator&=(x lhs, x rhs) \
    { \
        lhs = static_cast<x>(static_cast<int32>(lhs) & static_cast<int32>(rhs)); \
    }

#define __ENUM_XOR_OPERATOR(x) \
    inline friend x operator^(x lhs, x rhs) \
    { \
        return static_cast<x>(static_cast<int32>(lhs) ^ static_cast<int32>(rhs)); \
    } \
    inline friend void operator^=(x lhs, x rhs) \
    { \
        lhs = static_cast<x>(static_cast<int32>(lhs) ^ static_cast<int32>(rhs)); \
    }