# include <light/Light.hpp>

using namespace Lightning;

Light::Light (double* c)
{
  memcpy(color, c, 3 * sizeof(double));
}

Light::~Light(void)
{
}

void Light::getColor(double c[3])
{
  memcpy(c, color, 3 * sizeof(double));
}

void Light::normalize(double p[4])
{
  double d = 0;

 for (int i = 0; i < 3; i++)
    d += p[i] * p[i];

  d = sqrt (d);
  for (int i = 0; i < 3; i++)
    p[i] /= d;
}

double Light::dot(double p1[4], double p2[4])
{
  double ps = 0;

 for (int i = 0; i < 3; i++)
    ps += p1[i] * p2[i];

  return ps;
}
