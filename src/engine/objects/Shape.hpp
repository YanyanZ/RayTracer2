#ifndef SHAPE_HPP
# define SHAPE_HPP

# include <iostream>

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
  protected:
    float coef_a; // Ambiante
    float coef_d; // Directionnelle
    float coef_s; // Speculaire
    float coef_t; // Reflection
    float coef_n; // Refraction
    float coef_shin; // Brillance
    RGBColor<float> color;

  public:
    Shape(RGBColor<float> c);
    virtual ~Shape(){};

  public:
    virtual bool hit(const Ray& r, float tmin, float tmax, float time,
		     HitRecord& hr);
    virtual bool shadowHit(const Ray& r, float tmin, float tmax, float time);

  public:
    virtual std::ostream& operator<<(std::ostream& out);
  };
}

#endif
