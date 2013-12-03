set(SOURCES RayTracer.cpp)

add_subdirectory(cameras)
add_subdirectory(engine)
#add_subdirectory(lights)
#add_subdirectory(materials)
#add_subdirectory(mesh)
add_subdirectory(parser)
add_subdirectory(random)
add_subdirectory(tools)
add_subdirectory(display)

add_library(RayTracer STATIC ${SOURCES})