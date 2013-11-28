#ifndef RANDOM_HPP
# define RANDOM_HPP

class Random
{
private:
  unsigned long long seed;
  unsigned long long mult;
  unsigned long long llong_max;
  float float_max;

public:
  ~Random();
  Random(unsigned long long _seed = 7564231ULL);

public:
  float operator()();
};

#endif
