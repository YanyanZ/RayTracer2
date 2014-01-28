#ifndef CHECKER_HPP
# define CHECKER_HPP

# include <stdlib.h>
# include <iostream>
# include <cmath>
# include <vector>

# include <tools/Transformer.hpp>

using namespace Tools;

namespace Texture
{
  class Checker
  {
  private:
    double size;
    std::vector<double> color1;
    std::vector<double> color2;
    Transformer* trans;

  public:
    Checker(void);
    virtual ~Checker(void);

  public:
    void setSize(double s);
    void setColor1(std::vector<double> c);
    void setColor2 (std::vector<double> c);
    void setTransformer(Transformer* trs);

  public:
    void getChecker(std::vector<double> pt, std::vector<double>& c);
  };
}

#endif
