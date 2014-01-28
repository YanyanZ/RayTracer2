
/***************************************************************************************/
/*						                                       */
/* Realise par : 	BONFORT THOMAS		                                       */
/*		        CHAIGNEAU DELPHINE	                                       */
/*			GALIZZI OLIVIER			                               */
/*			HEIGEAS LAURE		                                       */
/*                                                                                     */
/* Date :		4/06/2001	                                               */
/*                                                                                     */
/* Commentaires : permet de generer un bruit coherent en 3d dimension                  */
/*                de faire un effet bois ou marbre ou simplement bruite en renvoyant   */
/*                une couleur                                                          */
/*                de faire du bump mapping procedural                                  */
/*                                                                                     */
/***************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

# include <perlin/PerlinNoise.hpp>

using namespace Generation;

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

PerlinNoise::PerlinNoise ()
{
  start = 1;
  alpha = 1.0;
  beta = 1.0;
  octave = 1;
  nbCouleurs = 1;
  colorMap[0][0] = 1.0;
  colorMap[0][1] = 1.0;
  colorMap[0][2] = 1.0;
  range[0] = 0.0;
  intensite = 10;
  typePerlin = PERLIN;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

PerlinNoise::~PerlinNoise ()
{
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::setAlpha (double alpha)
{
  this->alpha = alpha;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::setBeta (double beta)
{
  this->beta = beta;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::setOctave (int octave)
{
  this->octave = octave;
}

void PerlinNoise::setTransformer(transformer * trans){
  this->trans=trans;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::setColorMap (int nbCouleurs, double colorMap[100][3],
			  double range[100])
{

  this->nbCouleurs = nbCouleurs;

  for (int i = 0; i < nbCouleurs; i++)
    this->range[i] = range[i];

  for (int i = 0; i < nbCouleurs; i++)
    for (int j = 0; j < 3; j++)
      this->colorMap[i][j] = colorMap[i][j];
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::setIntensite (double intensite)
{
  this->intensite = intensite;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::setWood ()
{
  this->typePerlin = WOOD;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::setMarble ()
{
  this->typePerlin = MARBLE;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::normalize2 (double v[2])
{
  double s;

  s = sqrt (v[0] * v[0] + v[1] * v[1]);
  v[0] = v[0] / s;
  v[1] = v[1] / s;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::normalize3 (double v[3])
{
  double s;

  s = sqrt (v[0] * v[0] + v[1] * v[1] + v[2] * v[2]);
  v[0] = v[0] / s;
  v[1] = v[1] / s;
  v[2] = v[2] / s;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::init (void)
{
  int i, j, k;

  for (i = 0; i < B; i++)
    {
      p[i] = i;
      g1[i] = (double) ((random () % (B + B)) - B) / B;

      for (j = 0; j < 2; j++)
	g2[i][j] = (double) ((random () % (B + B)) - B) / B;
      normalize2 (g2[i]);

      for (j = 0; j < 3; j++)
	g3[i][j] = (double) ((random () % (B + B)) - B) / B;
      normalize3 (g3[i]);
    }

  while (--i)
    {
      k = p[i];
      p[i] = p[j = random () % B];
      p[j] = k;
    }

  for (i = 0; i < B + 2; i++)
    {
      p[B + i] = p[i];
      g1[B + i] = g1[i];
      for (j = 0; j < 2; j++)
	g2[B + i][j] = g2[i][j];
      for (j = 0; j < 3; j++)
	g3[B + i][j] = g3[i][j];
    }
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

double
PerlinNoise::noise3 (double vec[3])
{
  int bx0, bx1, by0, by1, bz0, bz1, b00, b10, b01, b11;
  double rx0, rx1, ry0, ry1, rz0, rz1, *q, sy, sz, a, b, c, d, t, u, v;
  int i, j;

  if (start)
    {
      start = 0;
      init ();
    }

  setup (0, bx0, bx1, rx0, rx1);
  setup (1, by0, by1, ry0, ry1);
  setup (2, bz0, bz1, rz0, rz1);

  i = p[bx0];
  j = p[bx1];

  b00 = p[i + by0];
  b10 = p[j + by0];
  b01 = p[i + by1];
  b11 = p[j + by1];

  t = s_curve (rx0);
  sy = s_curve (ry0);
  sz = s_curve (rz0);

  q = g3[b00 + bz0];
  u = at3 (rx0, ry0, rz0);
  q = g3[b10 + bz0];
  v = at3 (rx1, ry0, rz0);
  a = lerp (t, u, v);

  q = g3[b01 + bz0];
  u = at3 (rx0, ry1, rz0);
  q = g3[b11 + bz0];
  v = at3 (rx1, ry1, rz0);
  b = lerp (t, u, v);

  c = lerp (sy, a, b);

  q = g3[b00 + bz1];
  u = at3 (rx0, ry0, rz1);
  q = g3[b10 + bz1];
  v = at3 (rx1, ry0, rz1);
  a = lerp (t, u, v);

  q = g3[b01 + bz1];
  u = at3 (rx0, ry1, rz1);
  q = g3[b11 + bz1];
  v = at3 (rx1, ry1, rz1);
  b = lerp (t, u, v);

  d = lerp (sy, a, b);

  return lerp (sz, c, d);
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

double
PerlinNoise::coherentNoise3D (double x, double y, double z)
{
  int i;
  double val, sum = 0;
  double p[3], scale = 1;

  p[0] = x;
  p[1] = y;
  p[2] = z;
  for (i = 0; i < octave; i++)
    {
      val = noise3 (p);
      sum += val / scale;
      scale *= alpha;
      p[0] *= beta;
      p[1] *= beta;
      p[2] *= beta;
    }

  return (sum);
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::PerlinColor (double pt[4], double coulObj[3])
{
  double p2[3];
  int i;
  double coef;

  trans->doTransformation(p2,pt);

  double val = coherentNoise3D (p2[0], p2[1], p2[2]);

  val = intensite * val;

  // normal 0.4 0.2 1 <5,5,5>
  switch (typePerlin)
    {
    case PERLIN:
      // normal 0.4 0.2 1 <5,5,5>
      if (val < -1)
	val = -0.99;
      if (val > 1)
	val = 0.99;
      break;
    case MARBLE:
      // marbre 0.3 0.3 4 <5,5,5>
      val = cos (p2[1] + val);
      break;
    case WOOD:
      //bois  0.4 0.2 1 <1,1,1>
      val = val * 20;
      val = val - (int) val;
      break;
    default:
      break;
    }

  // tous
  val = (1.0 + val) / 2.0;

  i = 0;
  while (i < nbCouleurs && range[i] <= val)
    i++;

  /* interpolation */
  coef = 1.0 / (range[i] - range[i - 1]);
  for (int j = 0; j < 3; j++)
    coulObj[j] =
      colorMap[i - 1][j] * (val - range[i - 1]) * coef +
      colorMap[i][j] * (range[i] - val) * coef;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
PerlinNoise::PerlinNormale (double pt[4], double normale[4])
{
  double p2[3];
  double v[3][2];
  double delta;

  trans->doTransformation(p2,pt);

  delta = 0.01;

  /* perlin noise */
  v[0][0] = coherentNoise3D (p2[0] + delta, p2[1], p2[2]);
  v[0][1] = coherentNoise3D (p2[0] - delta, p2[1], p2[2]);

  v[1][0] = coherentNoise3D (p2[0], p2[1] + delta, p2[2]);
  v[1][1] = coherentNoise3D (p2[0], p2[1] - delta, p2[2]);

  v[2][0] = coherentNoise3D (p2[0], p2[1], p2[2] + delta);
  v[2][1] = coherentNoise3D (p2[0], p2[1], p2[2] - delta);

  // normal 0.4 0.2 1 <5,5,5>
  for (int i = 0; i < 3; i++)
    {
      v[i][0] = intensite * v[i][0];
      v[i][1] = intensite * v[i][1];
    }

  // normal 0.4 0.2 1 <5,5,5>
  switch (typePerlin)
    {
    case PERLIN:
      // normal 0.4 0.2 1 <5,5,5>
      for (int i = 0; i < 3; i++)
	{
	  v[i][0] = intensite * v[i][0];
	  v[i][1] = intensite * v[i][1];
	}
      break;
    case MARBLE:
      // marbre 0.3 0.3 4 <5,5,5>
      for (int i = 0; i < 3; i++)
	{
	  v[i][0] = intensite * cos (p2[1] + v[i][0]);
	  v[i][1] = intensite * cos (p2[1] + v[i][1]);
	}
      break;
    case WOOD:
      //bois  0.4 0.2 1 <1,1,1>
      for (int i = 0; i < 3; i++)
	{
	  v[i][0] = v[i][0] * 20;
	  v[i][0] = v[i][0] - (int) v[i][0];
	  v[i][1] = v[i][1] * 20;
	  v[i][1] = v[i][1] - (int) v[i][1];
	  v[i][0] = intensite * v[i][0];
	  v[i][1] = intensite * v[i][1];
	}
      break;
    default:
      break;
    }

  normale[0] += v[0][0] - v[0][1];
  normale[1] += v[1][0] - v[1][1];
  normale[2] += v[2][0] - v[2][1];
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
