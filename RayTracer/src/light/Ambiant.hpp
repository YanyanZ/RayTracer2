#ifndef AMBIANT_HPP
# define AMBIANT_HPP

# include <vector>

# include <light/Light.hpp>

namespace Lightning
{
  class Ambiant : public Light
  {
  public:
    Ambiant(std::vector<double> c);
    virtual ~Ambiant(void);
  };
}

#endif
