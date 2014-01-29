# include <light/Directional.hpp>

using namespace Lightning;

Directional::Directional(std::vector<double> dir,
			 std::vector<double> c)
  : Light(c), direction (dir)
{
}

Directional::~Directional(void)
{
}

void Directional::getDirection (std::vector<double> dir)
{
  dir = direction;
}

void Directional::getShiness(Ray* r,
			     std::vector<double> p,
			     std::vector<double> n,
			     Object* o,
			     std::vector<double> l)
{

  std::vector<double> reflect = {0, 0, 0, 0};
  std::vector<double> c2 = {0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  double ps1, ps2;

  o->getColor(p, c2);

  for(int i = 0; i < 3; i++)
    dir[i]= -direction[i];

  normalize(dir);

  ps1 = dot(n, dir);

  for (int i = 0; i < 3; i++)
    reflect[i] = 2 * ps1 * n[i] - dir[i];
  reflect[3] = 0;

  normalize(reflect);
  ps2 = -r->dot(reflect);

  if (ps1 > 0.0)
    if (ps2 > 0.0)
    {
      for (int i = 0; i < 3; i++)
	l[i] = c2[i] * (o->getRhoD() * c2[i] * ps1 +
		       o->getRhoS() * pow(ps2, o->getShininess()));
    }
    else
    {
      for (int i = 0; i < 3; i++)
	l[i] = c2[i] * (o->getRhoD() * c2[i] * ps1);
    }
  else
  {
    l[0] = 0;
    l[1] = 0;
    l[2] = 0;
  }
}
