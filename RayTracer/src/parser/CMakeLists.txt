SET(SOURCES SceneParser.cpp)

add_subdirectory(xml)

add_library(Parser STATIC ${SOURCES})
target_link_libraries(Parser PugiXML)
