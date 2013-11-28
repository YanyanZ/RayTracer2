set(SOURCES Image.cpp)

find_package (OpenCV REQUIRED)

add_library(Display STATIC ${SOURCES})

target_link_libraries(Display ${OpenCV_LIBRARIES})