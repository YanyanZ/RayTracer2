# include <object/Plan.hpp>

Plan::Plan(void)
 : Object()
{
}

Plan::~Plan(void)
{
}

double Plan::hit(Ray* r, std::vector<double> i)
{
  double d;

  std::vector<double> p = {0, 0, 0, 0};
  std::vector<double> temp = {0, 0, 0, 0};
  std::vector<double> pos = {0, 0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  std::vector<double> pos2 = {0, 0, 0, 0};
  std::vector<double> dir2 = {0, 0, 0, 0};

  r->getOrigin(pos);
  r->getDirection(dir);

  trans->transformInv(pos2, pos);
  trans->transformInv(dir2, dir);

  double t;
  if (dir2[0] != 0)
  {
    t = -pos2[0] / dir2[0];
    if (t > epsilon)
    {
      p[0] = 0.0;
      p[1] = pos2[1] + dir2[1] * t;
      p[2] = pos2[2] + dir2[2] * t;
      p[3] = 1.0;

      d = distance(p, pos2);
      trans->transform(i,p);

      return d;
    }
    else
      return MAXDOUBLE;
  }
  else
    return MAXDOUBLE;
}

void Plan::normal(std::vector<double> p, Ray* r,
		  std::vector<double> normal)
{
  std::vector<double> p2 = {0, 0, 0, 0};

  trans->transformationInv(p2, p);

  normal[0] = 1;
  normal[1] = 0;
  normal[2] = 0;
  normal[3] = 0;

  checkNormal(normal, p2, r);
}
