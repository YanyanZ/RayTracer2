SET(SOURCES SceneParser.cpp
    pugixml.cpp)

add_library(Parser STATIC ${SOURCES})
target_link_libraries(Parser Tools)
