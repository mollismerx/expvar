#pragma once

#include "expvar/Operand.hpp"
#include <type_traits>

namespace expvar
{

template <typename T, typename Context, int N>
struct Variable
{
    template <typename U>
    static constexpr bool uses = std::is_same_v<Variable, U>;
    using Type = T;
    Type val_{};
    // masquerade as function to allow generic code 
    T operator()() const { return val_; }
    void init() { };
    Variable& operator=(T val) { val_ = val; return *this; }
    template <typename... E>
    static auto compile(E&... expr)
    {
      // for all expr find this Variable template class instance in expr and create lambda that sets it
      // return lambda that calls all created lambdas
      return [... lambda = expr.template compile<Variable>()](Type val) mutable { (lambda(val), ...); };
    }
};

template <typename T, typename Context, int N>
constexpr bool isOperand<Variable<T, Context, N>> = true;

} // namespace expvar
