cmake_minimum_required(VERSION 3.5)
project(w_lox CXX)

include(CheckIncludeFileCXX)

check_include_file_cxx(any HAS_ANY)
check_include_file_cxx(string_view HAS_STRING_VIEW)
check_include_file_cxx(coroutine HAS_COROUTINE)

set(CMAKE_CXX_STANDARD 20)

set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

add_executable(${PROJECT_NAME} main.cc)

aux_source_directory(scanner SCA_SRC)
aux_source_directory(types TYP_SRC)
aux_source_directory(errors_and_debug EAD_SRC)
aux_source_directory(ast AST_SRC)

target_include_directories(${PROJECT_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR})

target_sources(${PROJECT_NAME} PRIVATE ${AST_SRC} ${SCA_SRC} ${TYP_SRC} ${EAD_SRC})

add_subdirectory(tests)

