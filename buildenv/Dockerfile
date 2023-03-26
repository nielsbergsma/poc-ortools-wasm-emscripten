FROM emscripten/emsdk:3.1.34

# install development dependencies
RUN apt update && apt install -y wget git file xz-utils unzip

## install wasi-sdk
# COPY packages/wasi-sdk_19.8gb8d6809f1722+m_amd64.deb /tmp/wasi-sdk_19.8gb8d6809f1722+m_amd64.deb
# RUN dpkg -i /tmp/wasi-sdk_19.8gb8d6809f1722+m_amd64.deb

# install wasmtime (dev build)
RUN wget https://github.com/bytecodealliance/wasmtime/releases/download/dev/wasmtime-dev-x86_64-linux.tar.xz -O /tmp/wasmtime-dev-x86_64-linux.tar.xz \
	&& tar xJf /tmp/wasmtime-dev-x86_64-linux.tar.xz -C /opt \
	&& mv /opt/wasmtime* /opt/wasmtime

# install wasmer
RUN mkdir -p /opt/wasmer \
	&& wget https://github.com/wasmerio/wasmer/releases/download/v3.1.1/wasmer-linux-amd64.tar.gz -O /tmp/wasmer-linux-amd64.tar.gz \
	&& tar xzf /tmp/wasmer-linux-amd64.tar.gz -C /opt/wasmer

# install bazel (with bazelisk)
RUN mkdir -p /opt/bazel/bin \
	&& wget https://github.com/bazelbuild/bazelisk/releases/download/v1.16.0/bazelisk-linux-amd64 -O /opt/bazel/bin/bazel \
	&& chmod +x /opt/bazel/bin/bazel \
	&& USE_BAZEL_VERSION="5.4.0" /opt/bazel/bin/bazel --version

# install binaryen (for wasm-opt)
RUN wget https://github.com/WebAssembly/binaryen/releases/download/version_112/binaryen-version_112-x86_64-linux.tar.gz -O /tmp/binaryen-version_112-x86_64-linux.tar.gz \
	&& tar xzf /tmp/binaryen-version_112-x86_64-linux.tar.gz -C /opt \
	&& mv /opt/binaryen* /opt/binaryen

# install protobuf
RUN mkdir -p /opt/protobuf \
	&& wget https://github.com/protocolbuffers/protobuf/releases/download/v21.12/protoc-21.12-linux-x86_64.zip -O /tmp/protoc-21.12-linux-x86_64.zip \
	&& unzip /tmp/protoc-21.12-linux-x86_64.zip -d /opt/protobuf

# clean up /tmp
RUN rm -rf /tmp/*

ENV PATH=/opt/bazel/bin:/opt/protobuf/bin:/opt/binaryen/bin:/opt/wasmer/bin:/opt/wasmtime:/opt/wasi-sdk/bin:$PATH
ENV CC=/emsdk/upstream/emscripten/emcc
ENV USE_BAZEL_VERSION="5.4.0"

WORKDIR /build

# build: docker build -t emscripten-buildenv --platform=linux/amd64 .
# run: docker run -v $PWD:/build -it emscripten-buildenv bash