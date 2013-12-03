# include <lights/Light.hpp>

Light::Ambiant::~Ambiant()
{
}

Light::Ambiant::Ambiant(const RGBColor<float> c)
  : Light(c)
{
}
