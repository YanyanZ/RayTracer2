# include <lights/Light.hpp>

Light::~Light()
{
}

Light::Light(const RGBColor<float> co)
  : c (co)
{
}

Light::Light(const RGBColor<float> co, const Vector<float> dirr)
  : c (co), dir (dirr)
{
}

Light::Light(RGBColor<float> co, Vector<float> dirr, Vector<float> o)
  : c (co), dir (dirr), origin (o)
{
}
