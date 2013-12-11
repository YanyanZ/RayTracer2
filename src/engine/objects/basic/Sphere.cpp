# include <engine/objects/basic/Sphere.hpp>

Objects::Basic::Sphere::~Sphere()
{
}

Objects::Basic::Sphere::Sphere(const Vector<float> o, float r, const RGBColor<float> c)
  : Shape(c), center (o), radius (r)
{
}

bool Objects::Basic::Sphere::hit(const Ray& r, float tmin, float tmax, float time,
				 HitRecord& hr)
{
  Vector<float> tmp = r.origin() - center;

  double a = Tools::Vector<float>::dot(r.direction(), r.direction());
  double b = 2 * Tools::Vector<float>::dot(r.direction(), tmp);
  double c = Tools::Vector<float>::dot(tmp, tmp) - radius * radius;

  double delta = b*b - 4 * a * c;

  if (delta > 0)
  {
    delta = sqrt(delta);
    double t = (-b - delta) / (2 * a);
    
    if (t < tmin)
      t = (-b + delta) / (2*a);
    if (t < tmin || t > tmax)
      return false;

    hr.t = t;
    hr.normal = Tools::Vector<float>::unitVector(r.origin() + r.direction() * t - center);
    hr.color = color;
    return true;
  }

  return false;
}

bool Objects::Basic::Sphere::shadowHit(const Ray& r, float tmin, float tmax, float time)
{
  Vector<float> tmp = r.origin() - center;

  double a = Tools::Vector<float>::dot(r.direction(), r.direction());
  double b = 2 * Tools::Vector<float>::dot(r.direction(), tmp);
  double c = Tools::Vector<float>::dot(tmp, tmp) - radius * radius;

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

std::ostream& Objects::Basic::Sphere::operator<<(std::ostream& out)
{
  out << "[SPHERE] ";
  out << "Center={" << center.x << ";" << center.y << ";" << center.z << "} ";
  out << "Radius=" << radius;
  out << "Color={" << color.r << ";" << color.g << ";" << color.b << "}";
  out << std::endl;

  return out;
}
