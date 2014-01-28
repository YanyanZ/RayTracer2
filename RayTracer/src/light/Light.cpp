# include <light/Light.hpp>

using namespace Lightness;

Light::Light (std::vector<double> c)
  : color (c)
{
}

Light::~Light(void)
{
}

void Light::getColor(std::vector<double> c)
{
  c = color;
}

void Light::normalize(std::vector<double> p)
{
  double d = 0;

 for (int i = 0; i < 3; i++)
    d += p[i] * p[i];

  d = sqrt (d);
  for (int i = 0; i < 3; i++)
    p[i] /= d;
}

double Light::dot(std::vector<double> p1, std::vector<double> p2)
{
  double ps = 0;

 for (int i = 0; i < 3; i++)
    ps += p1[i] * p2[i];

  return ps;
}
