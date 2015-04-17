#pragma once
//------------------------------------------------------------------------------
/**
	@file core/enum.h

	Macros useful for managing enums. Faster if constexpr is available.

	(C) 2015 See the LICENSE file.
*/
#include <string.h>

#if JARVIS_USE_CONSTEXPR
constexpr int __EnumStringHash(const char* ptr)
{
	int hash = 0;
	int len = strlen(ptr);
	int i;
	for (i = 0; i < len; i++)
	{
		hash += ptr[i];
		hash += hash << 10;
		hash ^= hash >> 6;
	}
	hash += hash << 3;
	hash ^= hash >> 11;
	hash += hash << 15;
	hash &= ~(1 << 31);
	return hash;
}

#define __SWITCHSTRING(x) switch (__EnumStringHash(x))
#define __FROMSTRING(x) case __EnumStringHash(#x) : return x;
#define __TOSTRING(x) case x : return #x;
#else
#define __SWITCHSTRING(x) auto __switch_str = x;
#define __FROMSTRING(x) if (0 == strcmp(#x, __switch_str)) return x;
#define __TOSTRING(x) case x : return #x;
#endif