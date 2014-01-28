#ifndef CONE_HPP
# define CONE_HPP

# include <vector>

# include <object/Object.hpp>
# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

namespace Form
{
  class Cone : public Object
  {
  private:
    double sRadius;
    double bRadius;
    double heigh;

  public:
    Cone(double sr, double br, double h);
    virtual ~Cone(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> normal);
  };
}

#endif
