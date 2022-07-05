#pragma once

#include <concepts>
#include <type_traits>

namespace expvar
{

template <typename T>
constexpr bool isOperand = false;

template <typename T>
concept Operand = isOperand<T> || std::is_integral_v<T> || std::is_floating_point_v<T>;

} // namespace expvar