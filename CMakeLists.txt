cmake_minimum_required(VERSION 3.6)
set(CMAKE_CXX_STANDARD 14)
project(gravity_falls_decoder)

find_package(Threads)

set(SOURCE_FILES
        # tests_crappy_string.cpp
        # tests_cyclic_array.cpp
        # tests_caesar.cpp
        tests_vigenere.cpp

        GoogleTest/gtest-death-test.cc
        GoogleTest/gtest-filepath.cc
        GoogleTest/gtest-port.cc
        GoogleTest/gtest-printers.cc
        GoogleTest/gtest-test-part.cc
        GoogleTest/gtest-typed-test.cc
        GoogleTest/gtest.cc
        GoogleTest/gtest_main.cc)

include_directories(GoogleTest)
add_executable(gravity_falls_decoder ${SOURCE_FILES})
target_link_libraries(gravity_falls_decoder ${CMAKE_LIBS_INIT} ${CMAKE_THREAD_LIBS_INIT})