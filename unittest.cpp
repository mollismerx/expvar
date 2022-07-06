#include "expvar/operator.hpp"
#include "expvar/VarSystem.hpp"

#include <cassert>

int main(int argc, char **argv)
{
    // use a VarSystem to define variables and hold the memory of expressions for the lifetime of their use
    expvar::VarSystem setup;
    // declare a type that is unique to make variables distinguishable
    struct Context;
    // create representations for some variables. The types listed are the types of the variables in order
    // the number of types correspond to the number of variables created. 
    auto vars = setup.makeVariables<Context, int, int, int>();
    // name the variables
    auto [v1, v2, v3] = vars;
    // assign initial values (optional)
    v1 = 2;
    v2 = 3;
    v3 = 4;
    // locals for unit testing / demonstration purposes
    int result = 0;
    int result1 = 0;
    int result2 = 0;
    int result3 = 0;
    // create expressions based on the variables and tie them to a lambda with operator>>
    auto e = (1 + v1 + v2) >> [&](int val) mutable { result = val; };
    auto e1 = (-v1) >> [&](int val) mutable { result1 = val; };
    auto e2 = (v1 + v2 * v3) >> [&](int val) mutable { result2 = val; };
    auto e3 = (v1 - 1 > v2) >> [&](bool cond) mutable
    {
        if (cond) result3 = 7;
        else result3 = 11;
    };
    // create setter lambdas for the variables by listing the expressions they take part in
    // setters may be used in callbacks where the data for the input variables arrives
    // setters can be copied to std::function<void(T)> where T is the variable type
    auto [v1Setter, v2Setter, v3Setter] = setup.makeSetters(vars, e, e1, e2, e3);
    // test intial values have been propagated to the tied lambdas
    assert(result == 6);
    assert(result1 == -2);
    assert(result2 == 14);
    assert(result3 == 11);
    // set v1 and update the values of the expressions
    v1Setter(5);
    // verify lambdas have been invoked
    assert(result == 9);
    assert(result1 == -5);
    assert(result2 == 17);
    assert(result3 == 7);
    // set v2 and update the values of the expressions
    v2Setter(6);
    assert(result == 12);
    assert(result1 == -5);
    assert(result2 == 29);
    assert(result3 == 11);
    // set v3 and update the values of the expressions
     v3Setter(7);
    assert(result == 12);
    assert(result1 == -5);
    assert(result2 == 47);
    assert(result3 == 11);
    return 0;
}