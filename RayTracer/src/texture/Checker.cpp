# include <texture/Checker.hpp>

using namespace Texture;

Checker::Checker(void)
  : size (1)
{
  color1[0] = 1;
  color1[1] = 1;
  color1[2] = 1;

  color2[0] = 0;
  color2[1] = 0;
  color2[2] = 0;
}

Checker::~Checker(void)
{
}

void Checker::setSize(double s)
{
  size = s;
}

void Checker::setColor1(double c[3])
{
  memcpy(color1, c, 3 * sizeof(double));
}

void
Checker::setColor2(double c[3])
{
  memcpy(color2, c, 3 * sizeof(double));
}

void Checker::setTransformer(Transformer* trs)
{
  trans = trs;
}

void Checker::getChecker(double pt[4],
			 double c[3])
{
  double p2[4];

  trans->transform(p2, pt);

  int xx = static_cast<int>(p2[0]  / size);
  int yy = static_cast<int>(p2[1] / size);
  int zz = static_cast<int>(p2[2] / size);

  bool xpair, ypair, zpair;

  xpair = ((abs (xx) % 2) == 0);
  ypair = ((abs (yy) % 2) == 0);
  zpair = ((abs (zz) % 2) == 0);

  if (p2[0] < 0)
    xpair = !xpair;
  if (p2[1] < 0)
    ypair = !ypair;
  if (p2[2] < 0)
    zpair = !zpair;

  if (zpair)
    if ((xpair && ypair) || (!xpair && !ypair))
      memcpy(c, color1, 3 * sizeof(double));
    else
      memcpy(c, color2, 3 * sizeof(double));
  else if ((xpair && ypair) || (!xpair && !ypair))
    memcpy(c, color2, 3 * sizeof(double));
  else
    memcpy(c, color1, 3 * sizeof(double));
}
