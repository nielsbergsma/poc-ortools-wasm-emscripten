# Proof of concept OR-Tools CP-SAT to WebAssembly (emscripten)

This repository shows how to compile a CP-SAT program (with Google's OR-Tools) as a Emscripten web module.

## Set up

This repository utilises [Google's Bazel](https://bazel.build/) build tool. Which allows for easy, and _selective_ building. 

A small patch for or-tools can be found in the [patches](patches/) directory. This disables `GetProcessMemoryUsage()`, since it's not avaiable in emscripten.

## Included example

[example.cc](/example.cc) is a modified version of the Simple SAT program. The original version can be found in the [ortools/sat/samples](https://github.com/google/or-tools/blob/v9.6/ortools/sat/samples/simple_sat_program.cc) directory of OR-Tools.

## Depedencies

Pull the prebuilt image from [Docker Hub](https://hub.docker.com/r/nielsbergsma/emscripten-buildenv).
```shell
docker pull nielsbergsma/emscripten-buildenv
```

Or alternatively, to build the environment locally, execute the following command in the [/buildenv](/buildenv) directory:

```shell
docker build -t emscripten-buildenv --platform=linux/amd64 .
``` 

_note: $PWD should point to the parent directory (where the WORKSPACE file is located)_

## Building

1. Start a shell session in the docker container:

```shell
docker run -v $PWD:/build -it nielsbergsma/emscripten-buildenv bash
```

2. Compile and link the example program (optimized):

```shell
bazel build --copt="-Oz" --copt="-DNDEBUG" --linkopt="-Oz" --strip=always :example-wasm
```
_(grab a fresh cup of coffee, this will take a while)_

3. Copy the files to output directory:

```shell
mkdir dist/
cp bazel-bin/example-wasm/example.{wasm,js} dist/
```
