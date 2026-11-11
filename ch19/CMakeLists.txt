cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter19 LANGUAGES CXX)

set(exercises
    ex19_06_08 ex19_09_10 ex19_14_18 ex19_19 ex19_21_25
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
