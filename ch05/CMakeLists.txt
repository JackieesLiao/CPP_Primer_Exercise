cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter05 LANGUAGES CXX)

set(exercises
    ex5_05_06 ex5_09_12 ex5_14 ex5_17
    ex5_19 ex5_20 ex5_21 ex5_23_25
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
