#ifndef SHAPE_HPP
# define SHAPE_HPP

# include <tools/Ray.hpp>
# include <tools/Color.hpp>
# include <tools/Vector.hpp>

using namespace Tools;

namespace Objects
{
  struct HitRecord
  {
    float t;
    Vector<float> normal;
    RGBColor<float> color;
  };

  class Shape
  {
  public:
    virtual bool hit(const Ray& r, float tmin, float tmax, float time,
		     HitRecord& hr) = 0;
    virtual bool shadowHit(const Ray& r, float tmin, float tmax, float time) = 0;
  };
}

#endif
