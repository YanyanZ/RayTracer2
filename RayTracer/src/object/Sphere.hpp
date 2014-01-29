#ifndef SPHERE_HPP
# define SPHERE_HPP

# include <vector>

# include <object/Object.hpp>
# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

using namespace Tools;

namespace Form
{
  class Sphere : public Object
  {
  private:
    double ray;;

  public:
    Sphere(double r);
    virtual ~Sphere(void);

  public:
    virtual double hit(Ray* r, double i[4]);
    virtual void normal(double p[4], Ray* r, double normal[4]);
  };
}

#endif // __SPHERE__
