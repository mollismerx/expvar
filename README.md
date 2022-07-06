# expvar
Expression variables - alternative programming logic

Limited documentation

Sometimes (e.g. in trading strategies), when programming logic depends on many input variables from different sources, the expressions (logical and mathematical) that make up the program can become scattered through different class methods, and a general overview of the logic is lost.
expvar offers a way to connect expressions to code (lambdas) all in one place. When a variable is changed the relevant expressions are updated - much like a spreadsheet - and the relevant lambdas are invoked.

See [unittest.cpp](https://github.com/mollismerx/expvar/blob/main/unittest.cpp) for examples.

expvar is C++20 built with [Bazel](https://bazel.build).
