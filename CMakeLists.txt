cmake_minimum_required(VERSION 3.16)

project("hassuttelu" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if(MSVC)
add_compile_options("/source-charset:utf-8" "/execution-charset:utf-8")
endif()

add_subdirectory("rutka")
add_subdirectory("hatsapuri")