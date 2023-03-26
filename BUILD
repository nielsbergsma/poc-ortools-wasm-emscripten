load("@rules_cc//cc:defs.bzl", "cc_binary")
load("@emsdk//emscripten_toolchain:wasm_rules.bzl", "wasm_cc_binary")

emscripten_linkopts = [
    "--closure 1",
    "-pre-js",
    "-s WASM=1",
    "-s MALLOC=emmalloc",
    "-s ALLOW_MEMORY_GROWTH=1",
    "-s DYNAMIC_EXECUTION=0",
    "-s TEXTDECODER=0",
#   "-s USE_PTHREADS=1",
    "-s ASSERTIONS=0",
    "-s EXPORT_ES6=1",
    "-s MODULARIZE=1",
    "-s ENVIRONMENT=web",
    "-s EXPORT_NAME=createSolver",
    "-s USE_ES6_IMPORT_META=1",      
    "-s DISABLE_EXCEPTION_CATCHING=1",
    "-s INCOMING_MODULE_JS_API=locateFile,instantiateWasm",
    "-s EXPORTED_FUNCTIONS=_malloc,_free,_solve",
]

cc_binary(
    name = "example",
    srcs = ["example.cc"],
    copts = ["--std=c++17", "-fno-stack-protector"],
    linkopts = ["-fno-stack-protector"] + emscripten_linkopts,
    deps = [
        "@com_google_ortools//ortools/sat:cp_model",
        "@com_google_ortools//ortools/sat:cp_model_solver"
    ],
)

wasm_cc_binary(
    name = "example-wasm",
    cc_target = ":example"
)

cc_binary(
    name = "service",
    srcs = ["service.cc"],
    copts = ["--std=c++17", "-fno-stack-protector"],
    linkopts = ["-fno-stack-protector"],
    deps = [
        "@com_google_ortools//ortools/sat:cp_model",
        "@com_google_ortools//ortools/sat:cp_model_solver"
    ],
)

wasm_cc_binary(
    name = "service-wasm",
    cc_target = ":service"
)