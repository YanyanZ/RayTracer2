#ifndef CUBE_HPP
# define CUBETROUE_HPP

# include <vector>

# include <object/Object.hpp>
# include <tools/Ray.hpp>
# include <tools/Tranformer.hpp>

namespace Form
{
  class Cube : public Object
  {
  public:
    Cube(void);
    virtual ~Cube(void);

  public:
    double hit(Ray* r, std::vector<double> i);
    void normal (std::vector<double> p, Ray* r,
		 std::vector<double> normal);
  };
}

#endif
