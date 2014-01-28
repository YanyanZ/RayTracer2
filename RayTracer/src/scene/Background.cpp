# include <scene/Background.hpp>

using namespace Engien;

Background::Background(std::vector<double> c)
  : color (c)
{
}

Background::~Background(void)
{
}

void Background::getBackground(std::vector<double> c)
{
  color = c;
}
