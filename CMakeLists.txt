cmake_minimum_required(VERSION 2.8.12)
project(GL-WES-V2)

set(GL_WES_LIB gl-wes-v2)

file(GLOB GL_WES_SRC "src/*.c")

add_library(${GL_WES_LIB} STATIC ${GL_WES_SRC})

target_compile_definitions(${GL_WES_LIB} PRIVATE REF_DLL WES_MANGLE_PREPEND)

target_include_directories(${GL_WES_LIB} PRIVATE "src")