SET(SOURCES lecteurCar.cc
  lecteurScene.cc
  lecteurSym.cc)

add_library(Parser STATIC ${SOURCES})