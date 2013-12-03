# include <lights/Light.hpp>

Light::Light(const RGBColor<float> co)
  : c (co)
{
}

Light::Light(const RGBColor<float> co, const Vector<float> dirr)
  : c (co), dir (dirr)
{
}
