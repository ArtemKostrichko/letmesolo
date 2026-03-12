cmake_minimum_required(VERSION 3.20)
project(matrix_calculator LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(MSVC)
    add_compile_options(/W4)
else()
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

add_library(matrix_core STATIC
        src/core/placeholder.cpp
)
target_include_directories(matrix_core PUBLIC src)

add_library(matrix_io STATIC
        src/io/placeholder.cpp
)
target_include_directories(matrix_io PUBLIC src)

add_library(matrix_util STATIC
        src/util/placeholder.cpp
)
target_include_directories(matrix_util PUBLIC src)

add_library(matrix_report STATIC
        src/report/placeholder.cpp
)
target_include_directories(matrix_report PUBLIC src)

add_executable(matrix_app
        src/app/main.cpp
)
target_link_libraries(matrix_app
        PRIVATE
        matrix_core
        matrix_io
        matrix_util
        matrix_report
)

enable_testing()

add_executable(matrix_tests
        tests/test_main.cpp
)
add_test(NAME matrix_tests COMMAND matrix_tests)