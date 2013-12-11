set (SOURCES
  objects/Shape.cpp
  objects/basic/Triangle.cpp
  objects/basic/Sphere.cpp)

add_library(Engine STATIC ${SOURCES})