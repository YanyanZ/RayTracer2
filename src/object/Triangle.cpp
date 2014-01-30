# include <object/Triangle.hpp>

using namespace Form;

Triangle::Triangle (double pp1[4], double pp2[4], double pp3[4])
  : Object()
{
  memcpy(p1, pp1, 4 * sizeof(double));
  memcpy(p2, pp2, 4 * sizeof(double));
  memcpy(p3, pp3, 4 * sizeof(double));
}

Triangle::~Triangle(void)
{
}

double Triangle::hit(Ray* r, double i[4])
{
  double dist;

  double p[4] = {0, 0, 0, 0};
  double pos[4] = {0, 0, 0, 0};
  double dir[4] = {0, 0, 0, 0};
  double pos2[4] = {0, 0, 0, 0};
  double dir2[4] = {0, 0, 0, 0};

  r->getOrigin (pos);
  r->getDirection (dir);

  trans->transformInv(pos2, pos);
  trans->transformInv(dir2, dir);

  double x1 = p2[0] - p1[0];
  double y1 = p2[1] - p1[1];
  double z1 = p2[2] - p1[2];
  double x2 = p3[0] - p1[0];
  double y2 = p3[1] - p1[1];
  double z2 = p3[2] - p1[2];

  double x3 = dir2[0];
  double y3 = dir2[1];
  double z3 = dir2[2];
  double xp = pos2[0];
  double yp = pos2[1];
  double zp = pos2[2];

  double dx = xp - p1[0];
  double dy = yp - p1[1];
  double dz = zp - p1[2];

  double D = z1 * y3 * x2 - y1 * z3 * x2 - x3 * z1 * y2 -
    y3 * x1 * z2 + z3 * x1 * y2 + x3 * y1 * z2;
  double u = (-y3 * dx * z2 + y3 * x2 * dz - x2 * z3 * dy +
	      dx * z3 * y2 - x3 * y2 * dz + x3 * dy * z2) / D;
  double v = (x3 * y1 * dz + z3 * x1 * dy - y1 * z3 * dx -
	      x3 * z1 * dy - y3 * x1 * dz + z1 * y3 * dx) / D;
  double t = (dx * z1 * y2 - dx * y1 * z2 - x1 * y2 * dz +
	      x1 * dy * z2 + x2 * y1 * dz - x2 * z1 * dy) / D;

  if (fabs (D) > epsilon && u > epsilon && v > epsilon
      && (u + v) <= 1 + epsilon)
  {
    p[0] = pos2[0] + dir2[0] * t;
    p[1] = pos2[1] + dir2[1] * t;
    p[2] = pos2[2] + dir2[2] * t;
    p[3] = 1.0;

    dist = distance(p, pos2);
    trans->transform(i, p);
  }
  else
    dist = MAXDOUBLE;

  return dist;
}

void Triangle::normal(double p[4], Ray* r, double normal[4])
{
  double pt[4] = {0, 0, 0, 0};
  double v1[4] = {p2[0] - p1[0], p2[1] - p1[1],
		  p2[2] - p1[2]};
  double v2[4] = {p3[0] - p1[0], p3[1] - p1[1],
		  p3[2] - p1[2]};

  trans->transformInv(pt, p);
  normal[0] = v1[1] * v2[2] - v1[2] * v2[1];
  normal[1] = v2[0] * v1[2] - v1[0] * v2[2];
  normal[2] = v1[0] * v2[1] - v1[1] * v2[0];
  normal[3] = 0.0;

  checkNormal(normal, pt, r);
}
