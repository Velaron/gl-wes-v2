cmake_minimum_required(VERSION 3.1)
project(gl-wes-v2)

set(XASH_GL_WES gl-wes-v2)
file(GLOB XASH_GL_WES_SRC "${PROJECT_SOURCE_DIR}/src/*.c")
add_library(${XASH_GL_WES} STATIC ${XASH_GL_WES_SRC})
target_compile_definitions(${XASH_GL_WES} PRIVATE REF_DLL WES_MANGLE_PREPEND)
target_include_directories(${XASH_GL_WES} PRIVATE "${PROJECT_SOURCE_DIR}/src")