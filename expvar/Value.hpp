#pragma once

#include "expvar/Operand.hpp"

namespace expvar
{

template <typename T>
struct Value
{
    T val_{};
    void operator()(T val) { val_ = val; }    
    T operator()() const { return val_; }
};

template <typename T>
constexpr bool isOperand<Value<T>> = true;

} // namespace expvar