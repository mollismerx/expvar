#pragma once

#include "expvar/Value.hpp"
#include <type_traits>

namespace expvar
{
template <typename T, bool isNumber = std::is_integral_v<T> || std::is_floating_point_v<T>>
struct Rep
{
    using Type = Value<T>;
};

template <typename T>
struct Rep<T, false>
{
    using Type = T;
};


} // namespace expvar