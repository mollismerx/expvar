package(default_visibility = ["//visibility:public"])

cc_library(
    name = "expvar",
    hdrs = glob(["**/*.hpp"])
)

cc_binary(
    name = "unittest",
    srcs = ["unittest.cpp"],
    copts = ["-g", "-std=c++20", ],
    deps = [ ":expvar", ],
)
