#ifndef SPHERE_HPP
# define SPHERE_HPP

# include <engine/Ray.hpp>
# include <tools/Vector.hpp>
# include <tools/Color.hpp>
# include <objects/Shape.hpp>

using namespace Tools;

namespace Objects
{
  namespace Basic
  {
    class Sphere : public Shape
    {
    private:
      Vector<float> center;
      float radius;
      RGBColor color;

    public:
      ~Sphere();
      Sphere(const Vector<float> o, float r, const RGBColor& c);

    public:
      virtual bool hit(const Ray& r, float tmin, float tmax, float time,
		       HitRecord& hr);
      virtual bool shadowHit(const Ray& r, float tmin, float tmax, float time);
    };
  }
}

#endif