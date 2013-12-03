#ifndef LIGHT_HPP
# define LIGHT_HPP

# include <tools/Color.hpp>
# include <tools/Vector.hpp>

using namespace Tools;

class Light
{
public:
  RGBColor<float> c;
  Vector<float> dir;

public:
  virtual ~Light();

public:
  Light(RGBColor<float> c, Vector<float> dir);
};

#endif
