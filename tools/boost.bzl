DEFAULT_COPTS = ["-Wno-unused-value", "-march=native"]

def boost_library(name, defines=None, deps=None, extra_srcs=None, extra_hdrs=None, linkopts=None):
    defines    = defines if defines != None else []
    deps       = deps if deps != None else []
    extra_srcs = extra_srcs if extra_srcs != None else []
    extra_hdrs = extra_hdrs if extra_hdrs != None else []
    linkopts   = linkopts if linkopts != None else []
    short_name = name.replace('boost_', '')

    return native.cc_library(
        name = name,
        visibility = ["//visibility:public"],
        defines = defines,
        hdrs = native.glob(['libs/%s/src/*.hpp' % short_name,
                            'boost/%s/**/*.ipp' % short_name]) + extra_hdrs,
        srcs = native.glob(['libs/%s/src/*.cpp' % short_name,
                            'boost/%s/detail/*.hpp' % short_name]) + extra_srcs,
        deps = deps,
        copts = DEFAULT_COPTS,
        linkopts = linkopts,
    )
