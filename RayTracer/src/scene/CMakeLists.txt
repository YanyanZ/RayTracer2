SET(SOURCES Camera.cpp
  Scene.cpp
  Tracer.cpp)

add_library(Scene STATIC ${SOURCES})
target_link_libraries(Scene Tools)