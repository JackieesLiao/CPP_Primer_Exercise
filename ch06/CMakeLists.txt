cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter06 LANGUAGES CXX)

set(exercises
    ex6_03_04 ex6_05 ex6_07 ex6_10_12 ex6_17
    ex6_21_24 ex6_25_27 ex6_33 ex6_38 ex6_44 ex6_51 ex6_54_56
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
