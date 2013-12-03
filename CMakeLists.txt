cmake_minimum_required (VERSION 2.6)

project (Raytracer C CXX)

set (PRG_NAME rt)
set (CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -g -Wall -Werror -Wno-unknown-pragmas")

set (SOURCE src/main.cpp)

include_directories (src)

add_subdirectory (src)

find_package (Boost REQUIRED)
find_package (OpenCV REQUIRED)

# Create a new executable
add_executable(${PRG_NAME} ${SOURCE})

# Add libs to the project
target_link_libraries(${PRG_NAME} ${Boost_LIBRARIES})
target_link_libraries(${PRG_NAME} ${OpenCV_LIBRARIES})

target_link_libraries(${PRG_NAME} RayTracer)
target_link_libraries(${PRG_NAME} Tools)
target_link_libraries(${PRG_NAME} Cameras)
target_link_libraries(${PRG_NAME} Display)
target_link_libraries(${PRG_NAME} Engine)
target_link_libraries(${PRG_NAME} PugiXML)
target_link_libraries(${PRG_NAME} Random)