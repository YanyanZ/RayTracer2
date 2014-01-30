# include <object/Plan.hpp>

using namespace Form;

Plan::Plan(void)
 : Object()
{
}

Plan::~Plan(void)
{
}

double Plan::hit(Ray* r, double i[4])
{
  double d;

  double p[4] = {0, 0, 0, 0};
  double pos[4] = {0, 0, 0, 0};
  double dir[4] = {0, 0, 0, 0};
  double pos2[4] = {0, 0, 0, 0};
  double dir2[4] = {0, 0, 0, 0};

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

void Plan::normal(double p[4], Ray* r, double normal[4])
{
  double p2[4] = {0, 0, 0, 0};

  trans->transformInv(p2, p);

  normal[0] = 1;
  normal[1] = 0;
  normal[2] = 0;
  normal[3] = 0;

  checkNormal(normal, p2, r);
}
