#pragma once

#include <any>
#include <functional>
#include <tuple>
#include <vector>
#include <utility>

namespace expvar
{

class VarSystem
{
public:
    template <typename Context, typename... Types>
    static auto makeVariables()
    {
        return makeVars<Context, Types...>(std::index_sequence_for<Types...>{});
    }
    template <typename... Var, typename... Expr>
    auto makeSetters(std::tuple<Var...> variables, Expr&&... expressions)
    {
        return makeLambdas(variables, std::index_sequence_for<Expr...>{}, std::forward<Expr>(expressions)...);
    }

private:
    template <typename Context, typename... Types, std::size_t... Index>
    static auto makeVars(std::index_sequence<Index...>)
    {
        return std::make_tuple(Variable<Types, Context, Index>{}...);
    }
    template <typename... Var, std::size_t... Index, typename... Expr>
    auto makeLambdas(std::tuple<Var...> variables, std::index_sequence<Index...>, Expr&&... expressions)
    {
        storage_.resize(sizeof...(expressions));
        auto lambdas = std::make_tuple(Var::compile(store(expressions, Index)...)...);
        (storage_[Index].second(), ...);
        return lambdas;
    }
    template <typename T>
    T& store(T&& expression, std::size_t index)
    {
        auto& [storage, initialiser] = storage_[index];
        T& expr = storage.emplace<T>(std::forward<T>(expression));
        initialiser = [&expr]() { expr.init(); };
        return expr;
    }
    std::vector<std::pair<std::any, std::function<void()>>> storage_;
};

} // namespace expvar