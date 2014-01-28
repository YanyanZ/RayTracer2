# include <tools/Ray.hpp>

using namespace Tools;

Ray::Ray (std::vector<double> orig, std::vector<double> dir)
  : origin (orig), direction (dir), in (false)
{
  normalize(direction);
}

Ray::Ray(void)
  : in (false)
{
}

Ray::~Ray(void)
{
}

void Ray::normalize(std::vector<double>& v)
{
  double d = 0;

  for (int i = 0; i < 3; i++)
    d += v[i] * v[i];

  d = sqrt (d);
  for (int i = 0; i < 3; i++)
    v[i] /= d;
}

void Ray::setDirection(std::vector<double> dir)
{
  direction = dir;
  normalize(direction);
}

void Ray::setOrigin(std::vector<double> orig)
{
  origin = orig;
}

void Ray::getDirection(std::vector<double>& dir)
{
  dir = direction;
}

void Ray::getOrigin(std::vector<double>& orig)
{
  origin = orig;
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

double Ray::dot(std::vector<double> vec)
{
  double ps = 0;

  for (int i = 0; i < 3; i++)
    ps += direction[i] * vec[i];

  return ps;
}
