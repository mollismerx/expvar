#pragma once

#include "expvar/Operand.hpp"
#include "expvar/Value.hpp"

namespace expvar
{

template <typename Operand, typename OP, typename Destination = Value<typename Operand::Type>>
struct UnaryExpr
{
    template <typename U>
    static constexpr bool uses = Operand::template uses<U>;

    using Type = typename Operand::Type; // maybe common type
    Operand operand_;
    OP op_;
    Destination val_;
    auto operator()() { return val_(); }
    template <typename V>
    auto compile()
    {
        if constexpr (std::is_same_v<V, Operand>)
        {
            return [this](Type val) mutable { operand_.val_ = val; val_(op_(val)); };
        }
        else if constexpr (Operand::template uses<V>)
        {
            // recurse on the Operand of unary operator to create a lambda that propagates
            // intermediate results up to the expression
            auto subLambda = operand_.template compile<V>();
            return [this, subLambda](Type val) mutable { subLambda(val); val_(op_(operand_())); };
        }
        else
        {
            // expression did not contain Variable -> return dead code
            return [](Type) {};
        }
    }
    void init()
    {
        operand_.init();
        val_(op_(operand_()));

    }
};

template <typename Operand, typename OP, typename Destination>
constexpr bool isOperand<UnaryExpr<Operand, OP, Destination>> = true;

} // namespace expvar