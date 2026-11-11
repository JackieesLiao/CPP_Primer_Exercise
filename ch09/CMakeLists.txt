cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter09 LANGUAGES CXX)

set(exercises
    ex9_04_05 ex9_13 ex9_14_16 ex9_18_20 ex9_26_28
    ex9_31 ex9_38 ex9_41_50 ex9_49 ex9_51 ex9_52
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
