#ifndef BOX_HPP
# define BOX_HPP

# include <vector>

# include <object/Object.hpp>
# include <object/Parallelogram.hpp>

# include <tools/Ray.hpp>

namespace Form
{
  class Box : public Object
  {
  private:
    double side;
    std::vector<Parallelogram*> sides;
    int hitSide;

  public:
    Box(double s);
    virtual ~Box(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p,
		Ray* r,
		std::vector<double> n);
  };
}

#endif
