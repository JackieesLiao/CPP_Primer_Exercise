cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter10 LANGUAGES CXX)

set(exercises
    ex10_01_02 ex10_03_04 ex10_06_07 ex10_09 ex10_11
    ex10_12_13 ex10_14_15 ex10_16_18_19 ex10_17 ex10_20
    ex10_21 ex10_22_24 ex10_25 ex10_27_28 ex10_29_31
    ex10_32 ex10_33 ex10_34_37 ex10_42
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
