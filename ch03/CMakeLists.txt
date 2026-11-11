cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter03 LANGUAGES CXX)

set(exercises
    ex3_02 ex3_04 ex3_05 ex3_06 ex3_08 ex3_10
    ex3_14_15 ex3_16_21 ex3_17 ex3_20_24 ex3_22 ex3_23 ex3_25
    ex3_31_32 ex3_35_36 ex3_39 ex3_40_41 ex3_42
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
