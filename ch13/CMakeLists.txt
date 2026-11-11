cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter13 LANGUAGES CXX)

set(exercises
    ex13_05_08_11 ex13_13_16 ex13_18 ex13_27 ex13_30_31
    ex13_34_37 ex13_39_40 ex13_42 ex13_44_48 ex13_58
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
