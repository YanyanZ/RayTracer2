#ifndef DIRECTIONAL_HPP
# define DIRECTIONAL_HPP

# include <lights/Light.hpp>

# include <tools/Color.hpp>
# include <tools/Vector.hpp>

using namespace Tools;

namespace Lights
{
  class Directional : public Light
  {
  public:
    virtual ~Directional(){};
    Directional(const RGBColor<float> c, const Vector<float> dir);
    
  public:
    void getBrightness(Ray r, Vector<float> p);
  };
}

#endif
