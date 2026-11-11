cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter02 LANGUAGES CXX)

set(exercises
    ex2_03_04 ex2_08 ex2_18 ex2_33_38
    ex2_41 ex2_42
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
