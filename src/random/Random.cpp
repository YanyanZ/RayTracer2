# include <random/Random.hpp>

Random::~Random()
{
}

Random::Random(unsigned long long _seed)
{
  seed = _seed;
  mult = 62089911ULL;
  llong_max = 4294967295ULL;
  float_max = 4294967295.0f;
}

float Random::operator()()
{
  seed = mult * seed;
  return (static_cast<float>(seed % llong_max) / float_max);
}
