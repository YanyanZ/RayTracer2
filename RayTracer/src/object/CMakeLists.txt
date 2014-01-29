SET(SOURCES #Box.cpp
#  Cone.cpp
#  Cube.cpp
#  Cylinder.cpp
  Object.cpp
#  Parallelogram.cpp
  Plan.cpp
#  Pyramid3.cpp
#  Pyramid4.cpp
  Sphere.cpp
#  Tore.cpp
#  Triangle.cpp
)

add_library(Object STATIC ${SOURCES})
target_link_libraries(Object Tools)
target_link_libraries(Object Texture)