cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter18 LANGUAGES CXX)

set(exercises
    ex18_06_08 ex18_13_18 ex18_20 ex18_21_24 ex18_26_27 ex18_29_30
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
