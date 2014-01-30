SET(SOURCES
  Object.cpp
  Plan.cpp
  Sphere.cpp
  Triangle.cpp
)

add_library(Object STATIC ${SOURCES})
target_link_libraries(Object Tools)
target_link_libraries(Object Texture)