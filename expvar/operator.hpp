#pragma once

#include "expvar/BinaryExpr.hpp"
#include "expvar/Operand.hpp"
#include "expvar/Rep.hpp"
#include "expvar/UnaryExpr.hpp"
#include "expvar/Variable.hpp"
#include <functional>

namespace expvar
{

template <template <typename> typename Op>
auto evaluate(Operand auto left, Operand auto right)
{
    using Left = typename Rep<decltype(left)>::Type;
    using Right = typename Rep<decltype(right)>::Type;
    return BinaryExpr<Left, Right, Op<void>>{left, right};
}

auto operator+(Operand auto left, Operand auto right)
{
    return evaluate<std::plus>(left, right);
}

auto operator-(Operand auto left, Operand auto right)
{
    return evaluate<std::minus>(left, right);
}

auto operator*(Operand auto left, Operand auto right)
{
    return evaluate<std::multiplies>(left, right);
}

auto operator/(Operand auto left, Operand auto right)
{
    return evaluate<std::divides>(left, right);
}

auto operator%(Operand auto left, Operand auto right)
{
    return evaluate<std::modulus>(left, right);
}

auto operator<(Operand auto left, Operand auto right)
{
    return evaluate<std::less>(left, right);
}

auto operator<=(Operand auto left, Operand auto right)
{
    return evaluate<std::less_equal>(left, right);
}

auto operator>(Operand auto left, Operand auto right)
{
    return evaluate<std::greater>(left, right);
}

auto operator>=(Operand auto left, Operand auto right)
{
    return evaluate<std::greater_equal>(left, right);
}

auto operator==(Operand auto left, Operand auto right)
{
    return evaluate<std::equal_to>(left, right);
}

auto operator!=(Operand auto left, Operand auto right)
{
    return evaluate<std::not_equal_to>(left, right);
}

auto operator&&(Operand auto left, Operand auto right)
{
    return evaluate<std::logical_and>(left, right);
}

auto operator||(Operand auto left, Operand auto right)
{
    return evaluate<std::logical_or>(left, right);
}

template <typename Left, typename Right, typename OP, typename Lambda>
auto operator>>(BinaryExpr<Left, Right, OP> duo, Lambda destination)
{
    return BinaryExpr{duo.left_, duo.right_, duo.op_, destination};
}

template <template <typename> typename Op>
auto evaluate(Operand auto operand)
{
    using Operand = typename Rep<decltype(operand)>::Type;
    return UnaryExpr<Operand, Op<void>>{operand};
}

auto operator-(Operand auto operand)
{
    return evaluate<std::negate>(operand);
}

auto operator!(Operand auto operand)
{
    return evaluate<std::logical_not>(operand);
}

template <typename Operand, typename OP, typename Lambda>
auto operator>>(UnaryExpr<Operand, OP> solo, Lambda destination)
{
    return UnaryExpr{solo.operand_, solo.op_, destination};
}

} // namespace expvar