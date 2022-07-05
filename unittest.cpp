#include "expvar/operator.hpp"
#include "expvar/VarSystem.hpp"

struct Context;
// TODO: support literals
int main(int argc, char **argv)
{
    expvar::VarSystem setup;

    auto vars = setup.makeVariables<Context, int, int, int>();
    auto [v1, v2, v3] = vars;
    v1 = 2;
    v2 = 3;
    v3 = 4;
    int result = 0;
    int result2 = 0;
    auto e = (v1 + v2) >> [&](int val) mutable { result = val; };
    auto e2 = (v1 + v2 * v3) >> [&](int val) mutable { result2 = val; };
    auto [v1Setter, v2Setter, v3Setter] = setup.makeSetters(vars, e, e2);
    v1Setter(5);
    v2Setter(6);
    v3Setter(7);
    return 0;
}