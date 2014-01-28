#ifndef TRANSFORMER_HPP
# define TRANSFORMER_HPP

# include <vector>
# include <stdlib.h>
# include <cmath>
# include <iostream>

namespace Tools
{
  class Transformer
  {
  private:
    std::vector<std::vector<double> > translation;
    std::vector<std::vector<double> > rotation;
    std::vector<std::vector<double> > scale;
    std::vector<std::vector<double> > transformation;
    std::vector<std::vector<double> > ptransformation;

  public:
    std::vector<std::vector<double> > invTranslation;
    std::vector<std::vector<double> > invRotation;
    std::vector<std::vector<double> > invScale;
    std::vector<std::vector<double> > invTransformation;

  public:
    Transformer(void);
    virtual ~Transformer(void);

  public:
    void loadZeroMatrix(std::vector<std::vector<double> > m);
    void loadIdMatrix(std::vector<std::vector<double> > m);
    void mult(std::vector<std::vector<double> >& res,
	      std::vector<std::vector<double> > mat1,
	      std::vector<std::vector<double> > mat2);
    void mult(std::vector<double>& res,
	      std::vector<double> point,
	      std::vector<std::vector<double> > mat);

  public:
    void setScale (std::vector<double> s);
    void setRotation (std::vector<double> r);
    void setTranslation(std::vector<double> trs);

  public:
    void transform(std::vector<double> res, std::vector<double> vec);
    void transformInv(std::vector<double> res, std::vector<double> vec);
    void normalize(std::vector<double>& v);
  };
}

#endif
