#pragma once

#include "expvar/Operand.hpp"
#include "expvar/Value.hpp"

namespace expvar
{

template <typename Left, typename Right, typename OP, typename Destination = Value<typename Left::Type>>
struct BinaryExpr
{
    template <typename U>
    static constexpr bool uses = Left::template uses<U> || Right::template uses<U>;

    using Type = typename Left::Type; // maybe common type
    Left left_;
    Right right_;
    OP op_;
    Destination val_;
    auto operator()() { return val_(); }
    template <typename V>
    auto compile()
    {
        if constexpr (std::is_same_v<V, Left>)
        {
            return [this](Type val) mutable { left_.val_ = val; val_(op_(val, right_())); };
        }
        else if constexpr (std::is_same_v<V, Right>)
        {
            return [this](Type val) mutable { right_.val_ = val; val_(op_(left_(), val)); };
        }
        else if constexpr (Left::template uses<V>)
        {
            // recurse on the Left side of binary operator to create a lambda that propagates
            // intermediate results up to the expression
            auto lSubLambda = left_.template compile<V>();
            if constexpr (Right::template uses<V>)
            {
                // cope for case where Variable is used on both Left and Right side of operator
                auto rSubLambda = right_.template compile<V>();
                return [this, lSubLambda, rSubLambda](Type val) mutable
                    { lSubLambda(val); rSubLambda(val); val_(op_(left_(), right_())); };
            }
            else
            {
                return [this, lSubLambda](Type val) mutable { lSubLambda(val); val_(op_(left_(), right_())); };
            }
        }
        else if constexpr (Right::template uses<V>)
        {
            auto rSubLambda = right_.template compile<V>();
            return [this, rSubLambda](Type val) mutable { rSubLambda(val); val_(op_(left_(), right_())); };
        }
        else
        {
            // expression did not contain Variable -> return dead code
            return [](Type) {};
        }
    }
};

template <typename Left, typename Right, typename OP, typename Destination>
constexpr bool isOperand<BinaryExpr<Left, Right, OP, Destination>> = true;

} // namespace expvar