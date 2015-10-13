#pragma once
//------------------------------------------------------------------------------
//  @file util/tuple.h
//	(C) 2015 See the LICENSE file.
//------------------------------------------------------------------------------

namespace JARVIS {
namespace Core {

//------------------------------------------------------------------------------
/**
    This following code enables us to create a tuple as an array, which can be used to 
    statically assert a variadic argument list conforms to an array-like format.
*/
template <typename T1, typename T2>
struct tuple_concat;

template <typename... T1, typename... T2>
struct tuple_concat<std::tuple<T1...>, std::tuple<T2...>>
{
    using type = std::tuple<T1..., T2...>;
};

template <typename T, int32 N>
struct ArrayTuple;

template <typename T>
struct ArrayTuple<T, 0>
{
    using type = std::tuple<>;
};

template <typename T, int32 N>
struct ArrayTuple
{
    using type = typename tuple_concat<typename ArrayTuple<T, N-1>::type,std::tuple<T>>::type;
};

template <typename... T>
struct Tuple
{
    using type = typename std::tuple<T...>;
};

//------------------------------------------------------------------------------
/**
    Returns true if variadic argument consists solely of type S
*/
template <typename S, typename... T>
constexpr bool AllAreSame()
{
    return std::is_same<typename ArrayTuple<S, sizeof...(T)>::type, typename Tuple<T...>::type>::value;
}

}} // namespace JARVIS::Core