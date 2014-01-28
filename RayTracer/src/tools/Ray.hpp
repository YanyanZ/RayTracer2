#ifndef RAY_HPP
# define RAY_HPP

# include <vector>
# include <cmath>

namespace Tools
{
  class Ray
  {
  private:
    std::vector<double> origin;
    std::vector<double> direction;
    bool in;

  public:
    Ray(std::vector<double> orig, std::vector<double> dir);
    Ray(void);
    virtual ~Ray(void);

  public:
    void setDirection(std::vector<double> dir);
    void setOrigin(std::vector<double> orig);
    void setIn(bool i);

  public:
    void getDirection(std::vector<double>& dir);
    void getOrigin(std::vector<double>& orig);

  public:
    void swapInOut(void);
    bool isIn(void);
    double dot(std::vector<double> vec);
    void normalize(std::vector<double>& v);
  };
}

#endif
