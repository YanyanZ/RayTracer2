#ifndef PLAN_HPP
# define PLAN_HPP

# include <tools/Vector.hpp>
# include <tools/Color.hpp>
# include <tools/Ray.hpp>

# include <engine/objects/Shape.hpp>

using namespace Tools;

namespace Objects
{
  namespace Basic
  {
    class Plan : public Shape
    {
    public:
      Vector<float> normal;
      Vector<float> point;

    public:
      ~Plan();
      Plan(const Vector<float> n, const Vector<float> p);

    public:
      virtual bool hit(const Ray& r, float tmin, float tmax, float time,
		       HitRecord& hr);
      virtual bool shadowHit(const Ray& r, float tmin, float tmax, float time);
    };
  }
}

#endif
