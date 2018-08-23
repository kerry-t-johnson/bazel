workspace(name = "cpptest")

new_local_repository(
	name        = "boost",
    build_file  = "BUILD.boost",
    path        = '/opt/sw/boost_1_67_0'
)

new_local_repository(
    name       = "pqxx",
    build_file = "BUILD.pqxx",
    path       = '/opt/sw/libpqxx-6.2.4'
)

new_local_repository(
	name       = "poco",
	build_file = "BUILD.poco",
	path       = '/opt/sw/poco-1.9.0'
)

new_local_repository(
    name       = "yaml",
    build_file = "BUILD.yaml",
    path       = '/opt/sw/yaml-cpp-yaml-cpp-0.6.2'
)

new_git_repository(
    name        = "gtest",
    build_file  = "BUILD.gtest",
    remote      = "https://github.com/google/googletest",
    tag         = "release-1.8.0",
)