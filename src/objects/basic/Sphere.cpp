# include <objects/basic/Sphere.hpp>

Objects::Basic::Sphere::~Sphere()
{
}

Objects::Basic::Sphere::Sphere(const Vector<float> o, float r, const RGBColor c)
  : center (o), radius (r); color (c)
{
}

bool Objects::Basic::Sphere::hit(const Ray& r, float tmin, float tmax, float time,
				 HitRecord& hr)
{
  Vector<float> tmp = r.origin - center;

  double a = dot(r.direction(), r.direction());
  double b = 2 * dot(r.direction(), tmp);
  double c = dot(tmp, tmp) - radius * radius;

  double delta = b*b - 4 * a * c;

  if (delta > 0)
  {
    delta = sqrt(delta);
    double t = (-b - delta) / (2 * a);
    
    if (t < tmin)
      t = (-b + delta) / (2*a);
    if (t < tmin || t > tmax)
      return false;

    rh.t = t;
    rh.normal = unitVector(r.origin() + t * r.direction() - center);
    rh.color = color;
    return true;
  }

  return false;
}

bool Objects::Basic::Sphere::shadowHit(const Ray& r, float tmin, float tmax, float time)
{
  Vector<float> tmp = r.origin - center;

  double a = dot(r.direction(), r.direction());
  double b = 2 * dot(r.direction(), tmp);
  double c = dot(tmp, tmp) - radius * radius;

  double delta = b*b - 4 * a * c;

  if (delta > 0)
  {
    delta = sqrt(delta);
    double t = (-b - delta) / (2 * a);
    
    if (t < tmin)
      t = (-b + delta) / (2*a);
    if (t < tmin || t > tmax)
      return false;

    return true;
  }

  return false;
}
