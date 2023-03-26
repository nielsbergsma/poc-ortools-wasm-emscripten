load("@bazel_tools//tools/build_defs/repo:http.bzl", "http_archive")
load("@bazel_tools//tools/build_defs/repo:git.bzl", "git_repository")

http_archive(
    name = "emsdk",
    strip_prefix = "emsdk-3.1.34/bazel",
    url = "https://github.com/emscripten-core/emsdk/archive/refs/tags/3.1.34.tar.gz",
)

load("@emsdk//:deps.bzl", emsdk_deps = "deps")
emsdk_deps()

load("@emsdk//:emscripten_deps.bzl", emsdk_emscripten_deps = "emscripten_deps")
emsdk_emscripten_deps(emscripten_version = "3.1.34")

load("@emsdk//:toolchains.bzl", "register_emscripten_toolchains")
register_emscripten_toolchains()

git_repository(
    name = "com_google_absl",
    remote = "https://github.com/abseil/abseil-cpp.git",
    tag = "20230125.0",
)

git_repository(
    name = "com_google_protobuf",
    remote = "https://github.com/protocolbuffers/protobuf.git",
    tag = "v21.12",
)

git_repository(
    name = "com_google_ortools",
    remote = "https://github.com/google/or-tools.git",
    tag = "v9.6",
    patch_args = ["-p1"],
    patches = ["//patches:or-tools.patch"],
)

# local_repository(
#     name = "com_google_absl",
#     path = "external/abseil-cpp",
# )
# 
# local_repository(
#     name = "com_google_protobuf",
#     path = "external/protobuf",
# )
# 
# local_repository(
#     name = "com_google_ortools",
#     path = "external/or-tools",
# )

load("@com_google_protobuf//:protobuf_deps.bzl", "protobuf_deps")
protobuf_deps()