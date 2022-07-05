# expvar
Expression variables - alternative programming logic

Limited documentation

Sometimes (e.g. in trading strategies), when programming logic depends on many input variables from different sources, the expressions (logical and mathematical) that make up the program can become scattered through different class methods, and a general overview is lost.
expvar offers a way to connect expressions to code (lambdas) all in one place. When a variable is changed the relevant expressions are updated and the relevant lambdas are run.

See unittest.cpp for examples.
