# include <texture/Checker.hpp>

using namespace Texture;

Checker::Checker(void)
  : size (1),
    color1 ({1.0, 1.0, 1.0}),
    color2 ({0.0, 0.0, 0.0})
{
}

Checker::~Checker(void)
{
}

void Checker::setSize(double s)
{
  size = s;
}

void Checker::setColor1(std::vector<double> c)
{
  color1 = c;
}

void
Checker::setColor2(std::vector<double> c)
{
  color2 = c;
}

void Checker::setTransformer(Transformer* trs)
{
  trans = trs;
}

void Checker::getChecker(std::vector<double> pt,
			 std::vector<double>& c)
{
  std::vector<double> p2;

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
      c = color1;
    else
      c = color2;
  else if ((xpair && ypair) || (!xpair && !ypair))
    c = color2;
  else
    c = color1;
}
