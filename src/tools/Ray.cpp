# include <tools/Ray.hpp>

Tools::Ray::~Ray()
{
}

Tools::Ray::Ray()
{
}

Tools::Ray::Ray(const Vector<float> a, const Vector<float> b)
{
  data[0].x = a.x;
  data[0].y = a.y;
  data[0].z = a.z;

  data[1].x = b.x;
  data[1].y = b.y;
  data[1].z = b.z;
}

Vector<float> Tools::Ray::origin() const
{
  return data[0];
}

Vector<float> Tools::Ray::direction() const
{
  return data[1];
}

Vector<float> Tools::Ray::pointAt(float t) const
{
  return (data[0] + data[1] * t);
}

std::ostream& Tools::Ray::operator<<(std::ostream& flux)
{
  flux << "(" << data[0] << ") + t(" << data[1] << ")";
  return flux;
}
