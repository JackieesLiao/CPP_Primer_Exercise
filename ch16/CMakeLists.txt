cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter16 LANGUAGES CXX)

set(exercises
    ex16_02_04 ex16_05_07 ex16_12_24 ex16_14_15 ex16_19_20
    ex16_21_22 ex16_28 ex16_37_39 ex16_40_41_42 ex16_53_56
    ex16_62 ex16_63_65
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
