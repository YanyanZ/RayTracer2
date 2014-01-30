#ifndef CHECKER_HPP
# define CHECKER_HPP

# include <cstring>
# include <cstdlib>
# include <iostream>
# include <cmath>

# include <tools/Transformer.hpp>

using namespace Tools;

namespace Texture
{
  class Checker
  {
  private:
    double size;
    double color1[3];
    double color2[3];
    Transformer* trans;

  public:
    Checker(void);
    virtual ~Checker(void);

  public:
    void setSize(double s);
    void setColor1(double c[3]);
    void setColor2 (double c[3]);
    void setTransformer(Transformer* trs);

  public:
    void getChecker(double pt[4], double c[3]);
  };
}

#endif
