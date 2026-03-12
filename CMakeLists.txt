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

add_library(matrix_core
        src/core/matrix.cpp
        src/core/linalg.cpp
)
target_include_directories(matrix_core PUBLIC src)

add_library(matrix_io
        src/io/matrix_input.cpp
        src/io/matrix_print.cpp
)
target_include_directories(matrix_io PUBLIC src)
target_link_libraries(matrix_io PUBLIC matrix_core)

add_library(matrix_util
        src/util/value_printer.cpp
)
target_include_directories(matrix_util PUBLIC src)
target_link_libraries(matrix_util PUBLIC matrix_core matrix_io)

add_library(matrix_report
        src/report/info_step.cpp
        src/report/transform_step.cpp
        src/report/property_step.cpp
        src/report/report_runner.cpp
)
target_include_directories(matrix_report PUBLIC src)
target_link_libraries(matrix_report PUBLIC matrix_core matrix_util)

add_executable(matrix_app
        src/app/main.cpp
)
target_link_libraries(matrix_app PRIVATE
        matrix_core
        matrix_io
        matrix_util
        matrix_report
)