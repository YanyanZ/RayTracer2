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
    std::vector<double> direction;

  public:
    Directional(std::vector<double> dir, std::vector<double> c);
    virtual ~Directional(void);

  public:
    void getDirection(std::vector<double> dir);
    void getShiness(Ray* r,
		    std::vector<double> p,
		    std::vector<double> n,
		    Object* o,
		    std::vector<double> l);

  };
}

#endif
