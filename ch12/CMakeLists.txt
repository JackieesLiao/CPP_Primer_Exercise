cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter12 LANGUAGES CXX)

set(exercises
    ex12_02 ex12_06_07 ex12_14_15 ex12_19_20_22
    ex12_23 ex12_24 ex12_26 ex12_27 ex12_32
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
