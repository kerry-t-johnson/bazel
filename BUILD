
cc_library(
    name        = 'logger',
    includes    = ['src/cpp/libs'],
    hdrs        = native.glob(['src/cpp/libs/logger/*.h']),
    srcs        = native.glob(['src/cpp/libs/logger/*.cpp']),
    deps        = ['//:util',
                   '@poco//:foundation',
                   '@poco//:json',
                   '@boost//:headers',
                   '@boost//:iostreams',
                   '@boost//:log',
                   '@boost//:system']
)

cc_library(
    name        = 'util',
    includes    = ['src/cpp/libs'],
    hdrs        = native.glob(['src/cpp/libs/util/*.h']),
    srcs        = native.glob(['src/cpp/libs/util/*.cpp']),
    deps        = ['@poco//:foundation',
                   '@poco//:json',
                   '@boost//:headers',
                   '@boost//:iostreams',
                   '@boost//:system']
)

cc_test(
    name = "logger_tests",
    srcs = native.glob(["test/cpp/libs/logger/*.cpp"]),
    deps = [
        "//:logger",
        "@gtest//:gtest_main",
        '@poco//:json',
        '@boost//:system'
    ],
)

cc_test(
    name = "util_tests",
    srcs = native.glob(["test/cpp/libs/util/*.cpp"]),
    deps = [
        "//:util",
        "@gtest//:gtest_main",
        '@poco//:json',
        '@boost//:iostreams',
        '@boost//:system'
    ],
)

cc_binary(
    name = "gelf_test",
    srcs = native.glob(["test/cpp/bins/gelf_test/*.cpp"]),
    deps = [
        "//:util",
        '//:logger',
        "@gtest//:gtest_main",
        '@poco//:json',
        '@boost//:program_options',
        '@boost//:system',
    ],
)
