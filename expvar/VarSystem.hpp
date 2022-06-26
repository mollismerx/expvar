#pragma once

#include <utility>
#include <tuple>
#include <any>
#include <vector>

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
        storage_.reserve(sizeof...(expressions));
        return std::make_tuple(Var::compile(store(expressions, storage_[Index])...)...);
    }
    template <typename T>
    static T& store(T&& expression, std::any& storage)
    {
        return storage.emplace<T>(std::forward<T>(expression));
    }
    std::vector<std::any> storage_;
};

} // namespace expvar