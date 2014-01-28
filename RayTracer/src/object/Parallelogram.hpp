#ifndef PARALLELOGRAM_HPP
# define PARALLELOGRAM_HPP

# include <vector>

# include <object/Object.hpp>
# include <tools/Ray.hpp>

using namespace Tools;

namespace Form
{
  class Parallelogram : public Object
  {
  private:
    std::vector<double> p1;
    std::vector<double> p2;
    std::vector<double> p3;
    std::vector<double> p4;

  public:
    Parallelogram(std::vector<double> pp1,
		  std::vector<double> pp2,
		  std::vector<double> pp3);
    virtual ~Parallelogram(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal(std::vector<double> p, Ray* r,
		std::vector<double> normal);
  };
}

#endif
