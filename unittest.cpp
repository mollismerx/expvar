#include "expvar/operator.hpp"
#include "expvar/VarSystem.hpp"

// TODO: support literals
int main(int argc, char **argv)
{
    struct Context;
    expvar::VarSystem setup;

    auto vars = setup.makeVariables<Context, int, int, int>();
    auto [v1, v2, v3] = vars;
    // v1 = 2;    
    int result = 0;
    auto e = (v1 + v2) >> [&](int val) mutable { result = val; };
    auto e2 = v1 + v2 + v3;
    auto [v1Setter, v2Setter, v3Setter] = setup.makeSetters(vars, e, e2);
    v1Setter(1);
    return 0;
}