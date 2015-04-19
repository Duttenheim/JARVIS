#pragma once
//------------------------------------------------------------------------------
/**
	@file core/enum.h

	Macros useful for managing enums. Instant if constexpr is available.

	(C) 2015 See the LICENSE file.
*/
#include <string.h>

#if __CONST_EXPR_SUPPORTED__
// const expression for string hashing
constexpr uint32 __EnumStringHash(const char* ptr)
{
    return !*ptr ? 5381 : (__EnumStringHash(ptr + 1) * 33) ^ *ptr;
}

#define __SWITCHSTRING(x) switch (__EnumStringHash(x))
#define __FROMSTRING(x) case __EnumStringHash(#x) : return x;
#define __TOSTRING(x) case x : return #x;
#else
#define __SWITCHSTRING(x) auto __switch_str = x;
#define __FROMSTRING(x) if (0 == strcmp(#x, __switch_str)) return x;
#define __TOSTRING(x) case x : return #x;
#endif