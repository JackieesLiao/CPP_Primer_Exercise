cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Chapter11 LANGUAGES CXX)

set(exercises
    ex11_03_04 ex11_07_08 ex11_09 ex11_12_13 ex11_14
    ex11_16_17 ex11_20_21 ex11_31_32 ex11_33 ex11_38
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
