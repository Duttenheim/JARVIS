#pragma once
//------------------------------------------------------------------------------
//  @file core/constness.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

#ifdef __CONST_EXPR_SUPPORTED__
#define STATIC_ASSERT static_assert
#define CONST_EXPR constexpr
#else
#define STATIC_ASSERT assert
#define CONST_EXPR const
#pragma message ("static assert will not truly be static if constexpr is not present...")
#endif

namespace JARVIS {
namespace Core {
// const expression for string hashing
inline CONST_EXPR uint32 __StringHash(const char* ptr)
{
    return !*ptr ? 5381 : (__StringHash(ptr + 1) * 33) ^ *ptr;
}

// forwarding function which doesn't require template repetition
template <class T>
inline CONST_EXPR T&&
Forward(T f) { return std::forward<T>(f); };

template <class T>
inline CONST_EXPR T&&
Move(T f) { return std::move(f); }

} // namespace JARVIS

// convenience functions which are to be used when one doesn't want verbose calls
template <class T>
inline CONST_EXPR T&&
Fw(T f) { return std::forward<T>(f); }

// same as above but for moves
template <class T>
inline CONST_EXPR T&&
Mv(T f) { return std::move(f); }

} // namespace Core

