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
    double color[4];

  public:
    Light(double* c);
    virtual ~Light(void);

  public:
    void normalize(double v[4]);
    double dot(double p1[4], double p2[4]);

  public:
    void getColor(double c[3]);
  };
}

#endif
