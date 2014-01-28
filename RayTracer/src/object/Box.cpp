# include "box.h"

box::box (double s)
  : Object(), side (s)
{
  double l = side / 2.0;
  std::vector<double> p1 = {l, l, -l, 1};
  std::vector<double> p2 = {l, l, l, 1};
  std::vector<double> p3 = {l, -l, l, 1};
  std::vector<double> p4 = {l, -l, -l, 1};
  std::vector<double> p5 = {-l, -l, -l, 1};
  std::vector<double> p6 = {-l, l, -l, 1};
  std::vector<double> p7 = {-l, l, l, 1};
  std::vector<double> p8 = {-l, -l, l, 1};

  Transformer *trans;
  trans = new transformer();

  sides.push_back(new Parallelogram(p1, p2, p4));
  sides.push_back(new parallelogram (p6, p7, p5));
  sides.push_back(new parallelogram (p1, p2, p6));
  sides.push_back(new parallelogram (p2, p7, p3));
  sides.push_back(new parallelogram (p3, p8, p4));
  sides.push_back(new parallelogram (p4, p5, p1));

  for(int i = 0; i < sides.size(); i++)
    sides[i]->setTransformer(trans);
}

box::~Box(void)
{
  if (sides)
    delete sides;
}

double Box::hit(Ray* r, std::vector<double> i)
{
  double d, d2;
  std::vector<double> i2 = {0, 0, 0, 0};
  std::vector<double> temp = {0, 0, 0, 0};
  std::vector<double> pos = {0, 0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  std::vector<double> pos2 = {0, 0, 0, 0};
  std::vector<double> dir2 = {0, 0, 0, 0};
  Ray* r2;

  r->getOrigin(pos);
  r->getDirection(dir);

  trans->transformInv(pos2, pos);
  trans->ransformInv(dir2, dir);

  r2 = new Ray(pos2, dir2);

  d = sides[0]->hit(r2, temp);
  if (d < MAXDOUBLE)
    hitSide = 0;
  else
    hitSide = -1;

  for (int j = 1; j < sides.size(); j++)
  {
    d2 = sides[j]->hit(r2, i2);
    if (d2 < d)
    {
      d = d2;
      temp = i2;
      hitSide = j;
    }
  }

  trans->transform(i, temp);
  return d;
}

void Box::normal(std::vector<double> p,
		Ray* r,
		std::vector<double> n)
{
  std::vector<double> pt = {0, 0, 0, 0};

  trans->transform(pt, p);
  for (int j = 0; j < 4; j++)
    normal[j] = 0.0;

  switch (faceIntersectee)
  {
    case 0:
      normal[0] = 1;
      break;
    case 1:
      normal[0] = -1;
      break;
    case 2:
      normal[1] = 1;
      break;
    case 3:
      normal[2] = 1;
      break;
    case 4:
      normal[1] = -1;
      break;
    case 5:
      normal[2] = -1;
      break;
    default:
      break;
    }

  checkNormal(Normal, pt, r);
}
