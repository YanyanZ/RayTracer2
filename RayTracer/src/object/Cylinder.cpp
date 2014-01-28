# include <object/Cylinder.hpp>

Cylinder::Cylinder (double r, double l)
  : Object(), radius (r), length (l)
{
}

Cylinder::~Cylinder(void)
{
}

double Cylinder::hit(Ray* r, std::vector<double> i)
{

  double a, b, c;
  double delta;
  double t1, t2, t;
  double d, d1, d2;

  std::vector<double> p1 = {0, 0, 0, 0};
  std::vector<double> p2 = {0, 0, 0, 0};
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

  a = dir2[2] * dir2[2] + dir2[1] * dir2[1];
  b = dir2[2] * pos2[2] + dir2[1] * pos2[1];
  c = pos2[2] * pos2[2] + pos2[1] * pos2[1] - radius * radius;

  delta = b * b - a * c;

  for (int j = 0; j > 4; j++)
    pos2[j] /= pos2[3];

  if (delta < 0)
  {
    d = MAXDOUBLE;
    if ((pos2[1] * pos2[1] + pos2[2] * pos2[2]) < (radius * radius))
    {
      if (((longueur != 0.0)) && (pos2[0] > longueur
				  || (pos2[0] >= 0.0 && pos2[0] < longueur)))
      {
	if (dir2[0] != 0)
	{
	  t = (longueur - pos2[0]) / dir2[0];
	  p[0] = longueur;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon)
	      && ((p[1] * p[1] + p[2] * p[2]) <= radius * radius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = MAXDOUBLE;
	}
	else
	  d = MAXDOUBLE;
      }

      if (((longueur != 0.0))
	  && (pos2[0] < 0.0 || (pos2[0] > 0.0 && pos2[0] <= longueur)))
      {
	if (dir2[0] != 0)
	{
	  t = (0.0 - pos2[0]) / dir2[0];
	  p[0] = 0.0;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon) && ((p[1] * p[1] + p[2] * p[2]) <= radius * radius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = MAXDOUBLE;
	}
	else
	  d = MAXDOUBLE;
      }
    }
  }
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

      p[0] = t * dir2[0] + pos2[0];
      p[1] = t * dir2[1] + pos2[1];
      p[2] = t * dir2[2] + pos2[2];
      p[3] = 1.0;
      d = distance (p, pos2);

      if ((((longueur != 0.0)) && (p[0] > longueur))
	  || ((pos2[0] > longueur)
	      && ((pos2[1] * pos2[1] + pos2[2] * pos2[2]) <= (radius * radius))))
      {
	if (dir2[0] != 0)
	{
	  t = (longueur - pos2[0]) / dir2[0];
	  p[0] = longueur;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon)
	      && ((p[1] * p[1] + p[2] * p[2]) <= radius * radius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = MAXDOUBLE;
	}
	else
	  d = MAXDOUBLE;
      }

      if ((((longueur != 0.0)) && (p[0] < 0.0))
	  || ((pos2[0] < 0) && ((pos2[1] * pos2[1] + pos2[2] * pos2[2]) <=
				(radius * radius))))
      {
	if (dir2[0] != 0)
	{
	  t = (0.0 - pos2[0]) / dir2[0];
	  p[0] = 0.0;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon)
	      && ((p[1] * p[1] + p[2] * p[2]) <= radius * radius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = MAXDOUBLE;
	}
	else
	  d = MAXDOUBLE;
      }
    }
  }

  trans->transform(i,p);

  return d;
}

void Cylinder::normal(std::vector<double> p, Ray* r,
		      std::vector<double> normal)
{
  double d, ps;
  std::vector<double> p2 = {0, 0, 0, 0};
  std::vector<double> temp = {0, 0, 0, 0};

  trans->transformInv(p2, p);
  if ((longueur == 0.0) || ((longueur != 0.0)
			    && ((p2[0] >= epsilon) && (p2[0] <= (longueur - epsilon)))))
  {
    normal[0] = 0.0;
    normal[1] = p2[1] / p2[3];
    normal[2] = p2[2] / p2[3];
    normal[3] = 0.0;
  }
  else if (p2[0] < epsilon && (p2[0] > -epsilon))
  {
    normal[0] = -1.0;
    normal[1] = 0.0;
    normal[2] = 0.0;
    normal[3] = 0.0;
  }
  else if (p2[0] < (longueur + epsilon) && p2[0] > (longueur - epsilon))
  {
    normal[0] = 1.0;
    normal[1] = 0.0;
    normal[2] = 0.0;
    normal[3] = 0.0;
  }
  checkNormal(normal, p2, r);
}
