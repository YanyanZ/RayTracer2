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
    virtual ~Plan(void);

  public:
    virtual double hit(Ray* r, double i[4]);
    virtual void normal(double p[4], Ray* r, double normal[4]);
  };
}

#endif
