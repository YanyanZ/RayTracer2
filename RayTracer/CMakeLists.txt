cmake_minimum_required (VERSION 2.6)

project (Raytracer C CXX)

set (PRG_NAME raytracer)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -gdwarf-2 -Wall  -Wno-unknown-pragmas")

set (SOURCE src/RayTracer.cpp)

include_directories (src)
add_subdirectory (src)

add_executable(${PRG_NAME} ${SOURCE})

target_link_libraries(${PRG_NAME} Parser)
target_link_libraries(${PRG_NAME} Scene)
target_link_libraries(${PRG_NAME} Light)
target_link_libraries(${PRG_NAME} Object)
