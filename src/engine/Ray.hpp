#ifndef RAY_HPP
# define RAY_HPP

# include <tools/Vector.hpp>

# include <iostream>

using namespace Tools;

namespace Engine
{
  class Ray
  {
  private:
    Vector<float> data[2];

  public:
    ~Ray();

  public:
    Ray();
    Ray(const Vector<float> a, const Vector<float> b);
    Ray(const Ray& r);

  public:
    Vector<float> origin() const;
    Vector<float> direction() const;
    Vector<float> pointAt(float t) const;

  public:
    Bool operator==(const Ray& r);
    Bool operator!=(const Ray& r);
    
  public:
    std::ostream operator<<(std::ostream flux, const Ray& r);
  };
}

#endif
