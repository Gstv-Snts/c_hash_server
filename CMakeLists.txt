cmake_minimum_required(VERSION 3.14)
project(c_hash_server C)

set(CMAKE_C_STANDARD 99)
set(CMAKE_C_STANDARD_REQUIRED true)

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_C_FLAGS "${CMAKE_C_FLGAS}  --coverage -lm")
set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -lm ")
set(CMAKE_BUILD_TYPE Debug)

include_directories(include)
include_directories(libs/Unity/src)

file(GLOB_RECURSE SOURCE_FILES src/*.c)
file(GLOB_RECURSE TESTS_FILES tests/*.c)

add_executable(main cmd/main.c ${SOURCE_FILES})
add_executable(bench cmd/bench.c ${SOURCE_FILES})
add_executable(tests ${TESTS_FILES} ${SOURCE_FILES})
add_library(Unity STATIC libs/Unity/src/unity.c)

include(FetchContent)

FetchContent_Declare(
  Unity
  GIT_REPOSITORY https://github.com/ThrowTheSwitch/Unity
  GIT_TAG v2.6.0
  SOURCE_DIR ${CMAKE_SOURCE_DIR}/libs/Unity)

FetchContent_MakeAvailable(Unity)

target_link_libraries(tests m)
target_link_libraries(main m)
target_link_libraries(bench m)
target_link_libraries(tests Unity)

enable_testing()
add_test(NAME tests COMMAND tests)
add_test(NAME mem_check_tests
         COMMAND valgrind --leak-check=full --error-exitcode=1
                 --track-origins=yes ./tests)
