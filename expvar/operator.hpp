#pragma once

#include "expvar/BinaryExpr.hpp"
#include "expvar/Operand.hpp"
#include "expvar/Rep.hpp"
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

template <typename Right, typename Left, typename OP, typename Lambda>
auto operator>>(BinaryExpr<Left, Right, OP> left, Lambda destination)
{
    return BinaryExpr{left.left_, left.right_, left.op_, destination};
}

} // namespace expvar