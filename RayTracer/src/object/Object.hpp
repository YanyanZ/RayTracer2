#ifndef OBJET_HPP
# define OBJET_HPP

# include <values.h>
# include <cmath>
# include <stdlib.h>
# include <iostream>

# include <tools/Ray.hpp>
# include <perlin/PerlinNoise.hpp>
# include <texture/Checker.hpp>
# include <tools/Polynomial.hpp>
# include <texture/Mapper.hpp>
# include <tools/Transformer.hpp>

using namespace Tools;
using namespace Texture;
using namespace Generator;

namespace Form
{
  class Object
  {
  public:
    enum {COLOR, TEXTURE, PERLIN, CHECKER, NO};

  protected:
    double epsilon;
    double rhoA;      /* coefficient attenuation lumiere ambiente */
    double rhoD;      /* coefficient attenuation lumiere directionnelle */
    double rhoS;      /* coefficient attenuation lumiere speculaire */
    double rhoR;      /* coefficient de reflection */
    double rhoT;      /* 1 - rhoR */
    double n;	      /* indice de refraction de l'objet */
    double shiness; /* brillance */
    double c[3];
    int tPigment;
    int tNormal;

  protected:
    Mapper *mapper;
    Checker *ccr;
    PerlinNoise *pColor;
    PerlinNoise *pNormale;
    Transformer * trans;

  public:
    Object(void);
    virtual ~Object(void);

  public:
    double distance(double* p1, double* p2);

  public:
    void setTransformer(Transformer* trs);
    void setEpsilon(double e);
    void setRhoA(double v);
    void setRhoD(double v);
    void setRhoR(double v);
    void setRhoS(double v);
    void setRhoT(double v);
    void setN(double v);
    void setShininess(double v);
    void setTypePigment(int t);
    void setColor(double colo[3]);
    void setChecker(Checker* cc);
    void setPerlin(PerlinNoise* pNoise);
    void setPerlinNormal(PerlinNoise* pNoise);
    void setTypeNormal(int type);
    void setMapper(Mapper* mp);

  public:
    double getEpsilon(void);
    double getRhoA(void);
    double getRhoD(void);
    double getRhoR(void);
    double getRhoS(void);
    double getRhoT(void);
    double getN(void);
    double getShininess(void);
    void getColor(double p[4], double c[3]);
    void getChecker(double p[4], double c[3]);
    double getRefractionIndex(void);

  public:
    bool tRay(Ray* r,
	      double i[4],
	      double normal[4],
	      Ray* r2);
    bool rRay(Ray* r,
	      double i[4],
	      double normal[4],
	      Ray* r2);

  public:
    virtual double hit(Ray* r, double i[4]);
    virtual void normal(double p[4], Ray* r,
			double normal[4]);

  public:
    void checkNormal(double n[4],
		     double p[4],
		     Ray* r);
  };
}
#endif
