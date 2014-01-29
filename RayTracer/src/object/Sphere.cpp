# include <object/Sphere.hpp>

using namespace Form;

Sphere::Sphere(double r)
  : Object(), ray (r)
{
}

Sphere::~Sphere(void)
{
}

double Sphere::hit(Ray* r,
		   std::vector<double> i)
{
  double a, b, c;
  double delta;
  double t1, t2, t;
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

  a = dir2[0] * dir2[0] + dir2[1] * dir2[1] + dir2[2] * dir2[2];
  b = dir2[0] * pos2[0] + dir2[1] * pos2[1] + dir2[2] * pos2[2];
  c = pos2[0] * pos2[0] + pos2[1] * pos2[1] + pos2[2] * pos2[2] -
    ray * ray;

  delta = b * b - a * c;

  if (delta <= 0)
    d = MAXDOUBLE;
  else
  {
    t1 = (-b + sqrt (delta)) / a;
    t2 = (-b - sqrt (delta)) / a;

    if (t1 <= epsilon && t2 <= epsilon)
      d = MAXDOUBLE;
    else
    {
      if ((t1 <= t2 && t1 > epsilon) || (t2 < t1 && t2 < epsilon))
	t = t1;
      else if ((t2 < t1 && t2 > epsilon) || (t1 < t2 && t1 < epsilon))
	t = t2;

      p[0] = t * dir2[0] + pos2[0] / pos2[3];
      p[1] = t * dir2[1] + pos2[1] / pos2[3];
      p[2] = t * dir2[2] + pos2[2] / pos2[3];
      p[3] = 1.0;
      d = distance (p, pos2);

      trans->transform(i, p);
    }
  }
  return d;
}

void Sphere::normal(std::vector<double> p, Ray* r,
		    std::vector<double> normal)
{
  std::vector<double> p2 = {0, 0, 0, 0};

 trans->transformInv(p2, p);
 normal[0] = p2[0] / p2[3];
 normal[1] = p2[1] / p2[3];
 normal[2] = p2[2] / p2[3];
 normal[3] = 0;

 checkNormal(normal, p2, r);
}