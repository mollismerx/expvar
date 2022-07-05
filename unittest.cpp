#include "expvar/operator.hpp"
#include "expvar/VarSystem.hpp"

#include <cassert>

struct Context;

int main(int argc, char **argv)
{
    expvar::VarSystem setup;

    auto vars = setup.makeVariables<Context, int, int, int>();
    auto [v1, v2, v3] = vars;
    v1 = 2;
    v2 = 3;
    v3 = 4;
    int result = 0;
    int result1 = 0;
    int result2 = 0;
    int result3 = 0;
    auto e = (1 + v1 + v2) >> [&](int val) mutable { result = val; };
    auto e1 = (-v1) >> [&](int val) mutable { result1 = val; };
    auto e2 = (v1 + v2 * v3) >> [&](int val) mutable { result2 = val; };
    auto e3 = (v1 - 1 > v2) >> [&](bool cond) mutable
    {
        if (cond) result3 = 7;
        else result3 = 11;
    };
    auto [v1Setter, v2Setter, v3Setter] = setup.makeSetters(vars, e, e1, e2, e3);
    assert(result == 6);
    assert(result1 == -2);
    assert(result2 == 14);
    assert(result3 == 11);
    v1Setter(5);
    assert(result == 9);
    assert(result1 == -5);
    assert(result2 == 17);
    assert(result3 == 7);
    v2Setter(6);
    assert(result == 12);
    assert(result1 == -5);
    assert(result2 == 29);
    assert(result3 == 11);
    v3Setter(7);
    assert(result == 12);
    assert(result1 == -5);
    assert(result2 == 47);
    assert(result3 == 11);
    return 0;
}
