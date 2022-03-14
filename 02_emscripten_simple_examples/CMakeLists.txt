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
            _call_js,\
            _invalid_memory_access,\
            _invoke_assert,\
            _throw_exception"
        --js-library ${CMAKE_CURRENT_LIST_DIR}/src/base/base_library.js
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
        "-sPTHREAD_POOL_SIZE=1"
)

set(PLATFORM Web CACHE STRING "Forcing PLATFORM_WEB")
add_subdirectory(src/graphics/raylib)

add_executable(graphics src/graphics/graphics.cpp)
target_link_options(graphics
    PRIVATE
        "-sENVIRONMENT=web"
        "-sUSE_GLFW=3"
        "-sEXPORTED_FUNCTIONS=\
            _main,\
            _update_draw_frame"
)
target_link_libraries(graphics PRIVATE raylib)
target_include_directories(graphics PRIVATE "${EMSCRIPTEN_ROOT_PATH}/system/include")
#set_target_properties(graphics PROPERTIES SUFFIX ".html")

install(
    TARGETS
        base
        fs
        threads
        graphics
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
        "${CMAKE_CURRENT_BINARY_DIR}/graphics.wasm"
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
