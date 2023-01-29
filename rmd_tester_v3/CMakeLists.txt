cmake_minimum_required(VERSION 3.20)

project(rmd_test.elf VERSION 0.0.1 LANGUAGES CXX)

find_package(libhal-lpc40xx REQUIRED CONFIG)
find_package(libhal-rmd REQUIRED CONFIG)

add_executable(${PROJECT_NAME} main.cpp newlib.cpp)
target_compile_features(${PROJECT_NAME} PRIVATE cxx_std_20)
target_include_directories(${PROJECT_NAME} PUBLIC .)
target_link_libraries(${PROJECT_NAME} PRIVATE libhal::lpc4078 libhal::rmd)
arm_cortex_post_build(${PROJECT_NAME})
