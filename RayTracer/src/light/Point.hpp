#ifndef POINT_HPP
# define POINT_HPP

# include <cstring>
# include <cstdio>

# include <light/Light.hpp>
# include <object/Object.hpp>

using namespace Form;
using namespace Tools;

namespace Lightning
{
  class Point : public Light
  {
  private:
    double position[4];
    double c1, c2, c3;

  public:
    Point(double *pos, double* c);
    virtual ~Point(void);

  public:
    void setDimming(double cc1,double cc2,double cc3);

  public:
    const double getC1 (void);
    const double getC2 (void);
    const double getC3 (void);

  public:
    void getShiness(Ray* r,
		    double p[4],
		    double n[4],
		    Object* o,
		    double l[3]);
    void getPosition (double pos[4]);
  };
}
#endif
