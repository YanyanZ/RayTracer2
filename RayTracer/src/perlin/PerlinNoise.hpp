#ifndef PERLINNOISE_HPP
# define PERLINNOISE_HPP

# include <stdlib.h>
# include <string.h>
# include <cmath>
# include <tools/Transformer.hpp>

using namespace Tools;

namespace Generator
{
  class PerlinNoise
  {
  private:
#define B 0x100
#define BM 0xff
#define N 0x1000
#define NP 12			/* 2^N */
#define NM 0xfff

#define s_curve(t) ( t * t * (3. - 2. * t) )
#define lerp(t, a, b) ( a + t * (b - a) )
#define setup(i,b0,b1,r0,r1)			\
    t = vec[i] + N;				\
    b0 = ((int)t) & BM;				\
    b1 = (b0+1) & BM;				\
    r0 = t - (int)t;				\
    r1 = r0 - 1.;
#define at2(rx,ry) ( rx * q[0] + ry * q[1] )
#define at3(rx,ry,rz) ( rx * q[0] + ry * q[1] + rz * q[2] )

  int p[B + B + 2];
  double g3[B + B + 2][3];
  double g2[B + B + 2][2];
  double g1[B + B + 2];
  int start;

  double alpha;
  double beta;
  int octave;
  int nbCouleurs;
  double colorMap[100][3];
  double range[100];
  double intensite;
  int typePerlin;


  void normalize2 (double v[2]);
  void normalize3 (double v[3]);
  void init (void);
  double noise3 (double vec[3]);
  double coherentNoise3D (double x, double y, double z);

    Transformer * trans;

  enum
  { PERLIN, WOOD, MARBLE };

public:

    PerlinNoise ();
    virtual ~PerlinNoise ();

  void setAlpha (double alpha);
  void setBeta (double beta);
  void setOctave (int octave);
  void setColorMap (int nbCouleurs, double colorMap[100][3],
		    double range[100]);
  void setIntensite (double intensite);
  void setWood ();
  void setMarble ();

  void setTransformer(Transformer * trans);

  void PerlinColor (double pt[4], double coulObj[3]);
  void PerlinNormale (double pt[4], double normale[4]);
  };
}

#endif // __PERLINNOISE__
