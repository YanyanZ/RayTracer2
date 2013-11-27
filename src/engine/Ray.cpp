# include <engine/Ray.hpp>

Engine::Ray::~Ray()
{
}

Engine::Ray::Ray()
{
  data[0] = Vector<float>();
  data[1] = Vector<float>();
}

Engine::Ray::Ray(const Vector<float> a, const Vector<float> b)
  : data[0] (a), data[1] (b)
{
}

Vector<float> Engine::Ray::origin()
{
  return data[0];
}

Vector<float> Engine::Ray::direction()
{
  return data[1];
}

Vector<float> Engine::Ray::pointAt(float t) const
{
  return data[0] + data[1] * t;
}

std::ostream operator<<(std::ostream flux)
{
  flux << "(" << data[0] << ") + t(" << data[1] << ")";
  return flux;
}
