#pragma once

#include <any>
#include <functional>
#include <map>
#include <tuple>
#include <typeindex>
#include <type_traits>
#include <utility>

template <typename T> struct Debug;
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
        auto lambdas = std::make_tuple(Var::compile(store(expressions)...)...);
        (storage_[typeid(std::decay_t<Expr>)].second(), ...);
        return lambdas;
    }

private:
    template <typename Context, typename... Types, std::size_t... Index>
    static auto makeVars(std::index_sequence<Index...>)
    {
        return std::make_tuple(Variable<Types, Context, Index>{}...);
    }
    template <typename T>
    T& store(T&& expression)
    {
        using Expr = std::decay_t<T>;
        auto [pos, insert] = storage_.try_emplace(typeid(Expr));
        auto& [storage, initialiser] = pos->second;
        if (insert)
        {
            Expr& expr = storage.emplace<Expr>(std::forward<Expr>(expression));
            initialiser = [&expr]() { expr.init(); };
            return expr;
        }
        else
        {
            return *std::any_cast<Expr>(&storage);
        }
    }
    std::map<std::type_index, std::pair<std::any, std::function<void()>>> storage_;
};

} // namespace expvar