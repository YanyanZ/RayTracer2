# include <tools/Ray.hpp>

using namespace Tools;

Ray::Ray (double orig[4], double dir[4])
  : in (false)
{
  memcpy(origin, orig, 4 * sizeof(double));
  memcpy(direction, dir, 4 * sizeof(double));
  normalize(direction);
}

Ray::Ray(void)
  : in (false)
{
}

Ray::~Ray(void)
{
}

void Ray::normalize(double v[4])
{
  double d = 0;

  for (int i = 0; i < 3; i++)
    d += v[i] * v[i];

  d = sqrt (d);
  for (int i = 0; i < 3; i++)
    v[i] /= d;
}

void Ray::setDirection(double dir[4])
{
  memcpy(direction, dir, 4 * sizeof(double));
  normalize(direction);
}

void Ray::setOrigin(double orig[4])
{
  memcpy(origin, orig, 4 * sizeof(double));
}

void Ray::getDirection(double dir[4])
{
  memcpy(dir, direction, 4 * sizeof(double));
}

void Ray::getOrigin(double orig[4])
{
  memcpy(orig, origin, 4 * sizeof(double));
}

void Ray::setIn(bool i)
{
  in = i;
}

void Ray::swapInOut(void)
{
  in = !in;
}

bool Ray::isIn(void)
 {
  return in;
}

double Ray::dot(double vec[4])
{
  double ps = 0;

  for (int i = 0; i < 3; i++)
    ps += direction[i] * vec[i];

  return ps;
}
