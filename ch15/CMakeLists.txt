cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter15 LANGUAGES CXX)

set(exercises
    ex15_03_05_11 ex15_18_20 ex15_26_28_29 ex15_30 ex15_39_41
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
