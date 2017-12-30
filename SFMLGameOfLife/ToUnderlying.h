#pragma once

#include <type_traits>

template <typename T>
// Converts given enum to its underlying type
constexpr typename std::underlying_type<T>::type toUnderlying(T enumerator)
{
	return static_cast<std::underlying_type<T>::type>(enumerator);
}