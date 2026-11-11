cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter07 LANGUAGES CXX)

set(exercises
    ex7_01 ex7_03 ex7_07 ex7_11_13 ex7_13
    ex7_21_22 ex7_21_bookstore ex7_23_29 ex7_31_32
    ex7_40_45 ex7_41 ex7_53_58
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
