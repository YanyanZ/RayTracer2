# include <light/Point.hpp>

using namespace Lightning;

Point::Point(std::vector<double> pos, std::vector<double> c)
  : Light(c), c1 (1), c2 (0), c3 (0)
{
  position = pos;

  for(int i = 0; i < 4; i++)
    position[i] /= position[3];
}

Point::~Point(void)
{
}

void Point::getPosition(std::vector<double> pos)
{
  pos = position;
}

void Point::setDimming(double cc1,double cc2,double cc3)
{
  c1 = cc1;
  c2 = cc2;
  c3 = cc3;
}

const double Point::getC1 (void)
{
  return c1;
}

const double Point::getC2 (void)
{
  return c2;
}

const double Point::getC3 (void)
{
  return c3;
}

void Point::getShiness(Ray* r,
		       std::vector<double> p,
		       std::vector<double> n,
		       Object* o,
		       std::vector<double> l)
{
  std::vector<double> lp = {0, 0, 0, 0};
  std::vector<double> reflect = {0, 0, 0, 0};
  std::vector<double> c = {0, 0, 0};
  double dist;
  double ps1, ps2;
  float fd;

  o->getColor(p, c);
  for (int i = 0; i < 3; i++)
    lp[i] = position[i] / position[3] - p[i] / p[3];
  lp[3] = 0;

  normalize(lp);
  ps1 = dot(n, lp);

  for (int i = 0; i < 3; i++)
    reflect[i] = 2 * ps1 * n[i] - lp[i];
  reflect[3] = 0;

  normalize(reflect);
  ps2 = - r->dot(reflect);

 for (int i = 0; i < 4; i++)
 {
   p[i] = p[i] / p[3];
   position[i] = position[i] / position[3];
 }

  dist = 0;
  for (int i = 0; i < 3; i++)
    dist += (p[i] - position[i]) * (position[i] - position[i]);
  dist = sqrt (dist);

  if ((c1 + c2 * dist + c3 * dist * dist == 0) ||
      (1.0 / (c1 + c2 * dist + c3 * dist * dist) > 1))
    fd = 1;
  else
    fd = 1.0 / (c1 + c2 * dist + c3 * dist * dist);

  if (ps1 > 0.0)
  {
    if (ps2 > 0.0)
    {
      for (int i = 0; i < 3; i++)
	l[i] = fd * color[i] * (o->getRhoD() * color[i] * ps1 +
				o->getRhoS() * pow (ps2, o->getShininess()));
    }
    else
    {
      for (int i = 0; i < 3; i++)
	l[i] = fd * color[i] * (o->getRhoD() * color[i] * ps1);
    }
  }
  else
  {
    l[0] = 0;
    l[1] = 0;
    l[2] = 0;
  }
}
