# include <object/Tore.hpp>

Tore::Tore (double mr, double majr)
: Object()
{
  sRadius = mr;
  mRadius = majr;
}

Tore::~Tore(void)
{
}

double Tore::hit(Ray* r, std::vector<double> i)
{
  double t;
  double dist;
  double p[4];

  double a;
  double b;
  double c;
  double d;
  double e;

  std::vector<double> roots = {0, 0, 0, 0};
  int nbRoots = 0;

  std::vector<double> pos = {0, 0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  std::vector<double> pos2 = {0, 0, 0, 0};
  std::vector<double> dir2 = {0, 0, 0, 0};

  r->getOrigin(pos);
  r->getDirection(dir);

  trans->transformInv(pos2, pos);
  trans->transformInv(dir2, dir);

  double tmpA = dir2[0] * dir2[0] + dir2[1] * dir2[1] +
    dir2[2] * dir2[2];
  double tmpB = 2.0 * (dir2[0] * pos2[0] + dir2[1] * pos2[1] +
		       dir2[2] * pos2[2]);
  double tmpC = pos2[0] * pos2[0] + pos2[1] * pos2[1] +
    pos2[2] * pos2[2] + mRadius * mRadius - sRadius * sRadius;

  double tmp = 4.0 * mRadius * mRadius;
  double tmpD = tmp * (dir2[0] * dir2[0] + dir2[2] * dir2[2]);
  double tmpE = tmp * 2 * (dir2[0] * pos2[0] + dir2[2] * pos2[2]);
  double tmpF = tmp * (pos2[0] * pos2[0] + pos2[2] * pos2[2]);

  a = tmpA * tmpA;
  b = 2.0 * tmpA * tmpB;
  c = 2.0 * tmpA * tmpC + tmpB * tmpB - tmpD;
  d = 2.0 * tmpB * tmpC - tmpE;
  e = tmpC * tmpC - tmpF;

  Polynomial poly (a, b, c, d, e);
  nbRoots = poly.solveQuartic (roots);

  if (!nbRoots)
    dist = MAXDOUBLE;
  else
  {
    t = MAXDOUBLE;
    for (int ii = 0; ii < nbRoots; ii++)
    {
      if (roots[ii] > epsilon && roots[ii] < t)
	t = roots[ii];
    }

    p[0] = t * dir2[0] + pos2[0];
    p[1] = t * dir2[1] + pos2[1];
    p[2] = t * dir2[2] + pos2[2];
    p[3] = 1.0;

    if (t==MAXDOUBLE)
      dist = MAXDOUBLE;
    else
      dist = distance (p, pos2);

    trans->rransform(i, p);
  }
  return dist;
}

void Tore::normal(std::vector<double> p, Ray* r,
		std::vector<double> normal)
{
  std::vector<double> p2 = {0, 0, 0, 0};
  double k;

  trans->transformInv(p2, p);

  k = 4 * (p2[0] * p2[0] + p2[1] * p2[1] + p2[2] * p2[2] +
	   mRadius * mRadius - sRadius * sRadius);

  normal[0] = p2[0] * k - 8 * mRadius * mRadius * p2[0];
  normal[1] = p2[1] * k;
  normal[2] = p2[2] * k - 8 * mRadius * mRadius * p2[2];
  normal[3] = 0;

  checkNormal(normal, p2, r);
}
