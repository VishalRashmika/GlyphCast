cmake_minimum_required(VERSION 3.10)

project(GlyphCast VERSION 0.1)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED True)

add_executable(glyph 
    src/GlyphCast.cpp
    src/Scanner.cpp
)

target_include_directories(glyph PRIVATE include)