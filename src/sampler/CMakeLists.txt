set(SOURCES Sampler.cpp
  Hammersley.cpp
  Jittered.cpp
  MultiJittered.cpp
  NRooks.cpp)

add_library(Sampler STATIC ${SOURCES})