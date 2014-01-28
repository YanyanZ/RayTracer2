# include <tools/Transformer.hpp>

using namespace Tools;

Transformer::Transformer(void)
  : translation ({{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}}),
    rotation  ({{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}}),
    scale ({{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}}),
    transformation ({{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}}),
    invTranslation ({{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}}),
    invRotation ({{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}}),
    invScale ({{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}}),
    invTransformation ({{0.0, 0.0, 0.0, 0.0}, {0.0, 0.0, 0.0, 0.0}})
{
}

Transformer::~Transformer(void)
{
}

void Transformer::mult(std::vector<double>& res,
		       std::vector<double> point,
		       std::vector<std::vector<double> > mat)
{
  int i, j;
  double val;

  for (i = 0; i < 4; i++)
  {
    val = 0;
    for (j = 0; j < 4; j++)
      val += mat[i][j] * point[j];
    res[i] = val;
  }

  if (res[3] != 0)
    for (i = 0; i < 4; i++)
      res[i] = res[i] / res[3];
}

void Transformer::mult(std::vector<std::vector<double> >& res,
		       std::vector<std::vector<double> > mat1,
		       std::vector<std::vector<double> > mat2)
{
  int i, j, k;
  double val;
  std::vector<std::vector<double> > r = {{0.0, 0.0, 0.0, 0.0},
					 {0.0, 0.0, 0.0, 0.0}};

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
    {
      val = 0;
      for (k = 0; k < 4; k++)
	val += mat1[i][k] * mat2[k][j];
      r[i][j] = val;
    }

  for (i = 0; i < 4; i++)
    for (j = 0; j < 4; j++)
      res[i][j] = r[i][j];
}

void Transformer::loadZeroMatrix(std::vector<std::vector<double> > m)
{

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      m[i][j] = 0;
}

void Transformer::loadIdMatrix(std::vector<std::vector<double> > m)
{
  loadZeroMatrix(m);

  for (int i = 0; i < 4; i++)
    m[i][i] = 1;
}

void Transformer::setTranslation(std::vector<double> trs)
{
  std::vector<std::vector<double> > temp = {{0.0, 0.0, 0.0, 0.0},
					    {0.0, 0.0, 0.0, 0.0}};

  loadIdMatrix(translation);
  for (int i = 0; i < 3; i++)
    translation[i][3] = trs[i];

  temp = transformation;
  mult(transformation, temp, translation);

  loadIdMatrix(invTranslation);
  for (int i = 0; i < 3; i++)
    invTranslation[i][3] = -trs[i];

  temp = invTransformation;
  mult(invTransformation, invTranslation, temp);
}

void Transformer::setRotation(std::vector<double> r)
{
  std::vector<std::vector<double> > rx= {{0.0, 0.0, 0.0, 0.0},
					 {0.0, 0.0, 0.0, 0.0}};
  std::vector<std::vector<double> > ry = {{0.0, 0.0, 0.0, 0.0},
					  {0.0, 0.0, 0.0, 0.0}};
  std::vector<std::vector<double> > rz = {{0.0, 0.0, 0.0, 0.0},
					  {0.0, 0.0, 0.0, 0.0}};
  std::vector<std::vector<double> > temp = {{0.0, 0.0, 0.0, 0.0},
					    {0.0, 0.0, 0.0, 0.0}};
  std::vector<std::vector<double> > temp2 = {{0.0, 0.0, 0.0, 0.0},
					    {0.0, 0.0, 0.0, 0.0}};

  loadIdMatrix(rx);
  loadIdMatrix(ry);
  loadIdMatrix(rz);

  rx[1][1] = cos(r[0]);
  rx[2][1] = sin(r[0]);
  rx[1][2] = -sin(r[0]);
  rx[2][2] = cos(r[0]);

  ry[0][0] = cos(r[1]);
  ry[2][0] = -sin(r[1]);
  ry[0][2] = sin(r[1]);
  ry[2][2] = cos(r[1]);

  rz[0][0] = cos (r[2]);
  rz[1][0] = sin (r[2]);
  rz[0][1] = -sin (r[2]);
  rz[1][1] = cos (r[2]);

  loadIdMatrix(rotation);
  mult(temp, rotation, rz);
  mult(temp2, temp, ry);
  mult(rotation, temp2, rx);

  temp = transformation;
  mult(transformation, temp, rotation);

  /* inversion de la matrice */
  rx[1][1] = cos (-r[0]);
  rx[2][1] = sin (-r[0]);
  rx[1][2] = -sin (-r[0]);
  rx[2][2] = cos (-r[0]);

  ry[0][0] = cos (-r[1]);
  ry[2][0] = -sin (-r[1]);
  ry[0][2] = sin (-r[1]);
  ry[2][2] = cos (-r[1]);

  rz[0][0] = cos (-r[2]);
  rz[1][0] = sin (-r[2]);
  rz[0][1] = -sin (-r[2]);
  rz[1][1] = cos (-r[2]);
  loadIdMatrix(this->invRotation);

  mult(temp, this->invRotation, rx);
  mult(temp2, temp, ry);
  mult(this->invRotation, temp2, rz);

  temp = invTransformation;
  mult(invTransformation, invRotation, temp);
}

void Transformer::setScale(std::vector<double> s)
{
  std::vector<std::vector<double> > temp = {{0, 0, 0, 0}, {0, 0, 0, 0}};
  loadIdMatrix(scale);

  for (int i = 0; i < 3; i++)
    scale[i][i] = s[i];

  temp = transformation;
  mult(transformation, temp, scale);

  loadIdMatrix(invScale);

  for (int i = 0; i < 3; i++)
    invScale[i][i] = 1.0 / s[i];

  temp = invTransformation;
  mult(invTransformation, invScale, temp);
}

void Transformer::transform(std::vector<double> res,
			    std::vector<double> vec)
{
  mult(res, vec, transformation);
  if (res[3]!=0)
    for(int i = 0; i < 4; i++)
      res[i]/=res[3];
}

void Transformer::transformInv(std::vector<double> res,
			       std::vector<double> vec)
{
  mult(res, vec, invTransformation);
  if (res[3]!=0)
    for(int i = 0; i < 4; i++)
      res[i]/=res[3];
}

void Transformer::normalize(std::vector<double>& p)
{

  double d = 0;

  for (int i = 0; i < 3; i++)
    d += p[i] * p[i];

  d = sqrt (d);
  for (int i = 0; i < 3; i++)
    p[i] /= d;
}
