set(SOURCES RayTracer.cpp)

add_subdirectories(cameras)
add_subdirectories(display)
add_subdirectories(engine)
add_subdirectories(lights)
add_subdirectories(materials)
add_subdirectories(mesh)
add_subdirectories(parser)
add_subdirectories(random)
add_subdirectories(tools)

add_library(RayTracer STATIC ${SOURCES})