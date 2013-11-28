#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include <tools/Vector.hpp>
# include <tools/Color.hpp>
# include <engine/Ray.hpp>
# include <engine/objects/Shape.hpp>

using namespace Tools;

namespace Objects
{
  namespace Basic
  {
    class Triangle : public Shape
    {
    public:
      Vector<float> s0;
      Vector<float> s1;
      Vector<float> s2;
      RGBColor<float> color;

    public:
      ~Triangle();
      Triangle(const Vector<float> _s0,
	       const Vector<float> _s1,
	       const Vector<float> _s2,
	       const RGBColor<float> rgv);

    public:
      virtual bool hit(const Ray& r, float tmin, float tmax, float time,
		       HitRecord& hr);
      virtual bool shadowHit(const Ray& r, float tmin, float tmax, float time);
    };
  }
}

#endif