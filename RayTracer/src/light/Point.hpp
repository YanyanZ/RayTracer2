#ifndef POINT_HPP
# define POINT_HPP

# include <vector>

# include <light/Light.hpp>

using namespace Form;

namespace Lightning
{
  class Point : public Light
  {
  private:
    std::vector<double> position;
    double c1, c2, c3;

  public:
    Point(std::vector<double> pos, std::vector<double> c);
    virtual ~Point(void);

  public:
    void setDimming(double cc1,double cc2,double cc3);

  public:
    const double getC1 (void);
    const double getC2 (void);
    const double getC3 (void);

  public:
    void getShiness(Ray* r,
		    std::vector<double> p,
		    std::vector<double> n,
		    Object* o,
		    std::vector<double> l);
    void getPosition (std::vector<double> pos);
  };
}
#endif
