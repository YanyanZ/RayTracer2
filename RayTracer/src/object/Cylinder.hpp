#ifndef CYLINDER_HPP
# define CYLINDER_HPP

# include <vector>

# include <object/Object.hpp>
# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

using namespace Tools;

namespace Form
{
  class cylindre : public Object
  {
  private:
    double radius;
    double lenght;

  public:
    Cylinder(double r, double l);
    virtual ~Cylinder(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> normal);
  };
}

#endif
