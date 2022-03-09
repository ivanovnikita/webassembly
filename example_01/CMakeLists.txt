cmake_minimum_required(VERSION 3.22)

project(wasm_examples)

if (NOT EMSCRIPTEN)
    message(FATAL_ERROR "Emscripten toolchain must be used")
endif()

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(base src/base/base.cpp)
target_link_options(base
    PRIVATE
        -fexceptions
        "-sENVIRONMENT=web"
        "-sEXPORTED_RUNTIME_METHODS=\
            cwrap,\
            UTF8ToString"
        "-sEXPORTED_FUNCTIONS=\
            _malloc,\
            _free,\
            _print_message,\
            _get_static_message,\
            _copy_message,\
            _get_allocated_message,\
            _invoke_assert,\
            _throw_exception"
)

add_executable(fs src/fs/fs.cpp)
target_link_options(fs
    PRIVATE
        -lidbfs.js
        --embed-file ${CMAKE_CURRENT_LIST_DIR}/src/fs/embed@/embed
        --preload-file ${CMAKE_CURRENT_LIST_DIR}/src/fs/preloaded@/preloaded
        "-sENVIRONMENT=web"
        "-sEXPORTED_RUNTIME_METHODS=\
            cwrap"
        "-sEXPORTED_FUNCTIONS=\
            _write_to_file,\
            _read_from_file"
)

add_executable(threads src/threads/threads.cpp)
target_compile_options(threads
    PRIVATE
        -pthread
)
target_link_options(threads
    PRIVATE
        -pthread
        "-sENVIRONMENT=web,worker"
        "-sEXPORTED_RUNTIME_METHODS=\
            cwrap"
        "-sEXPORTED_FUNCTIONS=\
            _sleep_in_another_thread"
)

install(
    TARGETS
        base
        fs
        threads
    DESTINATION
        "."
)
install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/base.wasm"
        "${CMAKE_CURRENT_BINARY_DIR}/fs.wasm"
        "${CMAKE_CURRENT_BINARY_DIR}/fs.data" # containes preloaded files
        "${CMAKE_CURRENT_BINARY_DIR}/threads.wasm"
        "${CMAKE_CURRENT_BINARY_DIR}/threads.worker.js"
        "src/server.py"
        "src/index.html"
        "src/base/base.html"
        "src/base/base_additional.js"
        "src/fs/fs.html"
        "src/fs/fs_additional.js"
        "src/threads/threads.html"
        "src/threads/threads_additional.js"
        "src/graphics/graphics.html"
        "src/graphics/graphics_additional.js"
    DESTINATION
        "."
)
install(
    PROGRAMS
        "src/server.py"
    DESTINATION
        "."
)
