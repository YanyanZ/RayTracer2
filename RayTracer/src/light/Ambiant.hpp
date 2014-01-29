#ifndef AMBIANT_HPP
# define AMBIANT_HPP

# include <vector>

# include <light/Light.hpp>

namespace Lightning
{
  class Ambiant : public Light
  {
  public:
    Ambiant(double c[3]);
    virtual ~Ambiant(void);
  };
}

#endif
