set (SOURCES Ray.cpp
  objects/basic/Triangle.cpp
  objects/basic/Sphere.cpp
  sampling/Sample.cpp)

add_library(Engine STATIC ${SOURCES})