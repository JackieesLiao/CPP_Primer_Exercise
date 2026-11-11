cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter17 LANGUAGES CXX)

set(exercises
    ex17_01_02 ex17_03 ex17_04_07 ex17_10_13 ex17_15_18
    ex17_21_22_24 ex17_28_30 ex17_34_36 ex17_37_39
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
