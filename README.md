# Install dependencies

* clang; 
* lld (for wasm-ld);
* [emscripten](https://emscripten.org/docs/getting_started/downloads.html#installation-instructions-using-the-emsdk-recommended) (3.0.0);

Optional:
* wabt (WebAssembly Binary Toolkit) (for wasm-objdump, wasm2wat);

# Build

## 01
```sh
cd webassembly/01_clang_simple_examples/module
make
cd ../memory
make
```

## 02
```sh
cd webassembly/02_emscripten_simple_examples
mkdir build
mkdir pages
cd build
ecmake cmake -DCMAKE_BUILD_TYPE=Release -DINSTALL_PREFIX_PATH=../pages ..
make install
```

# Run

## 01
```sh
cd webassembly/01_clang_simple_examples/module
python -m http.server
```

```sh
cd webassembly/01_clang_simple_examples/memory
python -m http.server
```

## 02

```sh
cd webassembly/02_emscripten_simple_examples/pages
./server.py
```

# Useful links

* Book "WebAssembly: The Definitive Guide: Safe, Fast, and Portable Code by Brian Sletten";
* Book "WebAssembly in Action by Gerard Gallant";
* Design rationale: https://github.com/WebAssembly/design/blob/main/Rationale.md
* Emscripten docs: https://emscripten.org/docs/porting/index.html
* V8 (JavaScript and WebAssembly engine from Google): 
    - https://v8.dev/docs
    - https://v8.dev/docs/embed
    - https://v8.dev/docs/wasm-compilation-pipeline
    - https://v8.dev/blog/liftoff
* Online wasm sandbox: https://webassembly.github.io/wabt/demo/wat2wasm/index.html
* WebAssembly interpreter: https://github.com/wasm3/wasm3
* Partial implementation of libc: https://github.com/PetterS/clang-wasm
* C/C++ DevTools Support (DWARF) (extension for Chrome): https://goo.gle/wasm-debugging-extension
* Wasm threads: https://dzone.com/articles/webassembly-threads-in-firefox