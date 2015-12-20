cmake_minimum_required(VERSION 3.3)
project(m2me)

set(CMAKE_C_FLAGS "-std=c99")

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}/bin")

set(SOURCE_FILES m2me.c wave.h byte_order.c byte_order.h wave.c)
add_executable(m2me ${SOURCE_FILES})