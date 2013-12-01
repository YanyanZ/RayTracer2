set(SOURCES Sampler.cpp
  Hammersley.cpp
  Jittered.cpp
  MultiJittered.cpp
  NRooks.cpp
  Regular.cpp)

add_library(Sampler STATIC ${SOURCES})