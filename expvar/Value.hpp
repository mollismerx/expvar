#pragma once

#include "expvar/Operand.hpp"

namespace expvar
{

template <typename T>
struct Value
{
    template <typename U>
    static constexpr bool uses = false;
    T val_{};
    void init() { }
    void operator()(T val) { val_ = val; }    
    T operator()() const { return val_; }
};

template <typename T>
constexpr bool isOperand<Value<T>> = true;

} // namespace expvar