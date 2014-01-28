SET(SOURCES Ambiant.cpp
  Light.cpp
  Directional.cpp
  Point.cpp)

add_library(Light STATIC ${SOURCES})
target_link_libraries(Light Tools)