#ifndef SAMPLE_HPP__
# define SAMPLE_HPP__

# define _XOPEN_SOURCE
# include <stdlib.h>

# include <cmath>
# include <tools/Vector.hpp>

using namespace Tools;

namespace Engine
{
  class Sample
  {
  public:
    static void random(Vector<float>* samples, int num_samples);
    static void jitter(Vector<float>* samples, int num_samples);
    static void nrooks(Vector<float>* samples, int num_samples);
    static void multiJitter(Vector<float>* samples, int num_samples);

  public:
    static void boxFilter(Vector<float>* samples, int num_samples);
    static void tentFilter(Vector<float>* samples, int num_samples);
    static void cubicSplineFilter(Vector<float>* samples, int num_samples);

  public:
    static void random(float* samples, int num_samples);
    static void jitter(float* samples, int num_samples);
    static void shuffle(float* samples, int num_samples);

  public:
    static float solve(float r);
    static float cubicFilter(float x);
  };
}

#endif
