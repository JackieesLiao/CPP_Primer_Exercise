cmake_minimum_required(VERSION 3.16)
project(CPP_Primer_Exercise LANGUAGES CXX)

set(chapters
    ch01 ch02 ch03 ch04 ch05 ch06 ch07 ch08 ch09 ch10
    ch11 ch12 ch13 ch14 ch15 ch16 ch17 ch18 ch19
)

foreach(chapter IN LISTS chapters)
    add_subdirectory(${chapter})
endforeach()
