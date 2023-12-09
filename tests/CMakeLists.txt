cmake_minimum_required(VERSION 3.5)
project(w_lox_test CXX)

include(FetchContent)
FetchContent_Declare(
  googletest
  GIT_REPOSITORY https://github.com/google/googletest.git
  GIT_TAG release-1.11.0
)
FetchContent_MakeAvailable(googletest)

function(add_wlox_test TEST_NAME TEST_SOURCE)
  add_executable(${TEST_NAME} ${TEST_SOURCE})

  aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../scanner SCANNER_SOURCES)
  aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../types TYPES_SOURCES)
  aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../errors_and_debug EAD_SOURCES)
  aux_source_directory(${CMAKE_CURRENT_SOURCE_DIR}/../ast AST_SOURCES)

  target_link_libraries(${TEST_NAME} PRIVATE gtest gtest_main)

  target_include_directories(${TEST_NAME} PRIVATE ${CMAKE_CURRENT_SOURCE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../)

  target_sources(${TEST_NAME} PRIVATE ${SCANNER_SOURCES} ${TYPES_SOURCES} ${AST_SOURCES} ${EAD_SOURCES})

  include(GoogleTest)
  gtest_discover_tests(${TEST_NAME})

endfunction()

add_wlox_test(NodeTypeTests node_types_test.cc)
add_wlox_test(ScannerTests scanner_test.cc)
add_wlox_test(PrettyPrinterTests pretty_printer_test.cc)

