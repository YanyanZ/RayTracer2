#ifndef AMBIANT_HPP
# define AMBIANT_HPP

# include <lights/Light.hpp>

# include <tools/Color.hpp>
# include <tools/Vector.hpp>

using namespace Tools;

namespace Light
{
  class Ambiant : public Light
  {
  public:
    ~Ambiant();
    Ambiant(const RGBColor<float> c);
  };
}

#endif
