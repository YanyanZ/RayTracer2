#ifndef LIGHT_HPP
# define LIGHT_HPP

# include <iostream>
# include <vector>
# include <values.h>
# include <stdlib.h>

# include <object/Object.hpp>
# include <tools/Ray.hpp>

using namespace Tools;

namespace Lightning
{
  class Light
  {
  protected:
    std::vector<double> color;

  public:
    Light(std::vector<double> c);
    virtual ~Light(void);

  public:
    void normalize(std::vector<double> v);
    double dot(std::vector<double> p1, std::vector<double> p2);

  public:
    void getColor(std::vector<double> c);
  };
}

#endif
