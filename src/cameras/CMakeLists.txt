set (SOURCES Camera.cpp)

add_library(Cameras STATIC ${SOURCES})

target_link_libraries(Cameras Tools)