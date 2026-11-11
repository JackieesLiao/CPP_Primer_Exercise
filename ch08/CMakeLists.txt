cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter08 LANGUAGES CXX)

set(exercises
    ex8_01 ex8_04 ex8_05 ex8_06_07_08 ex8_09
    ex8_10 ex8_11 ex8_13
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
