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
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> normal);
  };
}

#endif // __SPHERE__
