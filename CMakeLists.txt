cmake_minimum_required(VERSION 3.5)
project(mc CXX)
find_package(LLVM REQUIRED CONFIG)
execute_process(
  COMMAND ${LLVM_TOOLS_BINARY_DIR}/llvm-config --ldflags
  OUTPUT_VARIABLE LLVM_LINK_FLAGS)

message(STATUS "found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")
message(STATUS "Using LLVM tools in: ${LLVM_TOOLS_BINARY_DIR}")
message(STATUS "Using LLVM link flags: ${LLVM_LINK_FLAGS}")

llvm_map_components_to_libnames(LLVM_LIBS core native)

include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

set(CMAKE_CXX_FLAGS "-std=c++14")

add_library(lang
token.cpp
lexer.cpp
parser.cpp
semantics.cpp
codegen.cpp)

target_link_libraries(lang ${LLVM_LIBS})

add_executable(mc main.cpp)
target_link_libraries(mc lang)
