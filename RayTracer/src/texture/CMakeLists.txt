SET(SOURCES Checker.cpp
#  Mapper.cpp
)

add_library(Texture STATIC ${SOURCES})
target_link_libraries(Texture Tools)