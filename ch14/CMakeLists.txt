cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter14 LANGUAGES CXX)

set(exercises
    ex14_02_09 ex14_07 ex14_16_18 ex14_22_45 ex14_23_28
    ex14_30_32 ex14_34_36 ex14_37_38 ex14_39 ex14_42
    ex14_44 ex14_48_49
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
