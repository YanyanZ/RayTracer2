#ifndef TORE_HPP
# define TORE_HPP

# include <vector>

# include <object/Object.hpp>
# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

namespace Form
{
  class Tore : public Object
  {
  private:
    double sRadius;
    double mRadius;

  public:
    Tore(double mr, double majr);
    virtual ~ Tore ();

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> normal);
  };
}

#endif // __TORE__
