#ifndef TRANSFORMER_HPP
# define TRANSFORMER_HPP

# include <cstring>
# include <cstdlib>
# include <cmath>
# include <iostream>

namespace Tools
{
  class Transformer
  {
  private:
    double translation[4][4];
    double rotation[4][4];
    double scale[4][4];
    double transformation[4][4];
    double ptransformation[4][4];

  public:
    double invTranslation[4][4];
    double invRotation[4][4];
    double invScale[4][4];
    double invTransformation[4][4];

  public:
    Transformer(void);
    virtual ~Transformer(void);

  public:
    void loadZeroMatrix(double [4][4]);
    void loadIdMatrix(double m[4][4]);
    void mult(double res[4][4],
	      double mat1[4][4],
	      double mat2[4][4]);
    void mult(double* res,
	      double point[4],
	      double mat[4][4]);

  public:
    void setScale (double s[3]);
    void setRotation (double r[4]);
    void setTranslation(double trs[4]);

  public:
    void transform(double res[4], double vec[4]);
    void transformInv(double res[4], double vec[4]);
    void normalize(double v[4]);
  };
}

#endif
