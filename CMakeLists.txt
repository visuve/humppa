cmake_minimum_required(VERSION 3.16)

project("hassuttelu" LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXECUTABLE_OUTPUT_PATH "..")
set(LIBRARY_OUTPUT_PATH "..")

if(MSVC)
add_compile_options("/source-charset:utf-8" "/execution-charset:utf-8")
endif()

add_subdirectory("rutka")
add_subdirectory("hatsapuri")
add_subdirectory("kuusi")
add_subdirectory("ruletti")
add_subdirectory("pultsarit")
add_subdirectory("syntetisaattori")
add_subdirectory("pertti")
add_subdirectory("tsydegeeli")
add_subdirectory("niukka")
add_subdirectory("poelkky")
