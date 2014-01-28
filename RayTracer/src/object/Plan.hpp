#ifndef PLAN_HPP
# define PLAN_HPP

# include <vector>

# include <object/Object.hpp>
# include <tools/Transformer.hpp>
# include <tools/Ray.hpp>

using namespace Tools;

namespace Form
{
  class Plan : public Object
  {
  public:
    Plan(void);
    virtual ~plan(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> normal);
  };
}

#endif
