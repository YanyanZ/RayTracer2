#ifndef RAY_HPP
# define RAY_HPP

# include <cstring>
# include <cstdio>
# include <vector>
# include <cmath>

namespace Tools
{
  class Ray
  {
  private:
    double origin[4];
    double direction[4];
    bool in;

  public:
    Ray(double orig[4], double dir[4]);
    Ray(void);
    virtual ~Ray(void);

  public:
    void setDirection(double dir[4]);
    void setOrigin(double orig[4]);
    void setIn(bool i);

  public:
    void getDirection(double dir[4]);
    void getOrigin(double orig[4]);

  public:
    void swapInOut(void);
    bool isIn(void);
    double dot(double vec[4]);
    void normalize(double v[4]);
  };
}

#endif
