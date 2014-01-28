#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include <vector>

# include <object/Object.hpp>
# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

using namespace Tools;

namespace Form
{
  class Triangle : public Object
  {
  private:
    std::vector<double> p1;
    std::vector<double> p2;
    std::vector<double> p3;

  public:
    Triangle(std::vector<double> pp1, std::vector<double> pp2,
	     std::vector<double> pp3);
    virtual ~Triangle(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> normal);
  };
}

#endif // __TRIANGLE__
