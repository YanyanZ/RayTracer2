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
    std::vector<double> c;
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
    double distance(std::vector<double> p1, std::vector<double> p2);

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
    void setColor(std::vector<double> colo);
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
    void getColor(std::vector<double> p, std::vector<double> c);
    void getChecker(std::vector<double> p, std::vector<double> c);
    double getRefractionIndex(void);

  public:
    bool tRay(Ray* r,
	      std::vector<double> i,
	      std::vector<double> normal,
	      Ray* r2);
    bool rRay(Ray* r,
	      std::vector<double> i,
	      std::vector<double> normal,
	      Ray* r2);

  public:
    virtual double hit(Ray* r, std::vector<double> i);
    virtual void normal(std::vector<double> p, Ray* r,
			std::vector<double> normal);

  public:
    void checkNormal(std::vector<double> n,
		     std::vector<double> p,
		     Ray* r);
  };
}
#endif
