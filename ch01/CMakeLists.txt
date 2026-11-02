cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter01 LANGUAGES CXX)

set(exercises
    ex1_01 ex1_02 ex1_03 ex1_04 ex1_05 ex1_06
    ex1_08 ex1_09 ex1_10 ex1_11 ex1_12
    ex1_13_a ex1_13_b ex1_13_c ex1_16 ex1_18
    ex1_19 ex1_20 ex1_21 ex1_22 ex1_23 ex1_25
)

foreach(exercise IN LISTS exercises)
    add_executable(${exercise} ${exercise}.cpp)
    target_compile_features(${exercise} PRIVATE cxx_std_11)
    set_target_properties(${exercise} PROPERTIES CXX_EXTENSIONS OFF)
    if(MSVC)
        target_compile_options(${exercise} PRIVATE /W4 /utf-8)
    else()
        target_compile_options(${exercise} PRIVATE -Wall -Wextra -pedantic)
    endif()
endforeach()
