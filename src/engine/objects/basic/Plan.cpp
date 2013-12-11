# include <engine/objects/basic/Plan.hpp>

Objects::Basic::Plan::~Plan()
{
}

Objects::Basic::Plan::Plan(const Vector<float> n, const Vector<float> p)
  : normal (n), point (p)
{
}

bool Objects::Basic::Plan::hit(const Ray& r, float tmin, float tmax, float time,
		       HitRecord& hr)
{
  Vector<float> tmp = (point - r.origin()) * normal;
  Vector<float> tmp2 = r.direction() * normal;

  if ((t < tmin) || (t > tmax))
    return false;

  hr.t = t;
  hr.normal = n;
  hr.color = RGBColor<float>(72, 118, 255);

  return true;
}

bool Objects::Basic::Plan::shadowHit(const Ray& r, float tmin, float tmax, float time)
{
  float t = (point - r.origin()) * normal / (r.direction() * normal);

  if ((t < tmin) || (t > tmax))
    return false;

  return true;
}

