# include <lights/Ambiant.hpp>

Lights::Ambiant::~Ambiant()
{
}

Lights::Ambiant::Ambiant(const RGBColor<float> c)
  : Light(c)
{
}
