#ifndef DIRECTIONAL_HPP
# define DIRECTIONNAL_HPP

# include <vector>

# include <object/Object.hpp>
# include <light/Light.hpp>

# include <tools/Ray.hpp>

using namespace Tools;
using namespace Form;

namespace Lightning
{
  class Directional : public Light
  {
  private:
    double direction[4];

  public:
    Directional(double* dir, double* c);
    virtual ~Directional(void);

  public:
    void getDirection(double dir[4]);
    void getShiness(Ray* r,
		    double p[4],
		    double n[4],
		    Object* o,
		    double l[3]);
  };
}

#endif
