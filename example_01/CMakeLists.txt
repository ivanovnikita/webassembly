cmake_minimum_required(VERSION 3.22)

project(wasm_example_01)

if (NOT EMSCRIPTEN)
    message(FATAL_ERROR "Emscripten toolchain must be used")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_SHARED_LINKER_FLAGS "${CMAKE_SHARED_LINKER_FLAGS} -s ENVIRONMENT=web")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -s ENVIRONMENT=web")

add_executable(wasm_example_01 src/main.cpp)
target_link_options(wasm_example_01 PRIVATE "-sEXPORTED_RUNTIME_METHODS=cwrap,UTF8ToString")
target_link_options(wasm_example_01
    PRIVATE
    "-sEXPORTED_FUNCTIONS=\
    _malloc,\
    _free,\
    _print_message,\
    _get_static_message,\
    _copy_message,\
    _get_allocated_message,\
    _invoke_assert,\
    _write_to_file,\
    _read_from_file" # build will fail if there is no such symbol
)

install(
    TARGETS
        wasm_example_01
    DESTINATION
        "."
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/wasm_example_01.wasm"
        "src/index.html"
        "src/ui.js"
    DESTINATION
        "."
)
