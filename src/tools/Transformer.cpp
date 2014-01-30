# include <tools/Transformer.hpp>

using namespace Tools;

Transformer::Transformer(void)
{
  loadIdMatrix(translation);
  loadIdMatrix(rotation);
  loadIdMatrix(scale);
  loadIdMatrix(invTranslation);
  loadIdMatrix(invRotation);
  loadIdMatrix(invScale);
  loadIdMatrix(transformation);
  loadIdMatrix(invTransformation);
}

Transformer::~Transformer(void)
{
}

void Transformer::mult(double* res,
		       double point[4],
		       double mat[4][4])
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

void Transformer::mult(double res[4][4],
		       double mat1[4][4],
		       double mat2[4][4])
{
  int i, j, k;
  double val;
  double r[4][4] = {{0.0, 0.0, 0.0, 0.0},
		      {0.0, 0.0, 0.0, 0.0},
		      {0.0, 0.0, 0.0, 0.0},
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

void Transformer::loadZeroMatrix(double m[4][4])
{

  for (int i = 0; i < 4; i++)
    for (int j = 0; j < 4; j++)
      m[i][j] = 0;
}

void Transformer::loadIdMatrix(double m[4][4])
{
  loadZeroMatrix(m);

  for (int i = 0; i < 4; i++)
    m[i][i] = 1;
}

void Transformer::setTranslation(double trs[3])
{
  double temp[4][4] = {{0.0, 0.0, 0.0, 0.0},
		       {0.0, 0.0, 0.0, 0.0},
		       {0.0, 0.0, 0.0, 0.0},
		       {0.0, 0.0, 0.0, 0.0}};

  loadIdMatrix(translation);
  for (int i = 0; i < 3; i++)
    translation[i][3] = trs[i];

  memcpy(temp, transformation, 4 * 4 * sizeof(double));
  mult(transformation, temp, translation);

  loadIdMatrix(invTranslation);
  for (int i = 0; i < 3; i++)
    invTranslation[i][3] = -trs[i];

  memcpy(temp, invTransformation, 4 * 4 * sizeof(double));
  mult(invTransformation, invTranslation, temp);
}

void Transformer::setRotation(double r[3])
{
  double rx[4][4]= {{0.0, 0.0, 0.0, 0.0},
		    {0.0, 0.0, 0.0, 0.0},
		    {0.0, 0.0, 0.0, 0.0},
		    {0.0, 0.0, 0.0, 0.0}};

  double ry[4][4] = {{0.0, 0.0, 0.0, 0.0},
		     {0.0, 0.0, 0.0, 0.0},
		     {0.0, 0.0, 0.0, 0.0},
		     {0.0, 0.0, 0.0, 0.0}};

  double rz[4][4] = {{0.0, 0.0, 0.0, 0.0},
		     {0.0, 0.0, 0.0, 0.0},
		     {0.0, 0.0, 0.0, 0.0},
		     {0.0, 0.0, 0.0, 0.0}};

  double temp[4][4] = {{0.0, 0.0, 0.0, 0.0},
		       {0.0, 0.0, 0.0, 0.0},
		       {0.0, 0.0, 0.0, 0.0},
		       {0.0, 0.0, 0.0, 0.0}};

  double temp2[4][4] = {{0.0, 0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0, 0.0},
			{0.0, 0.0, 0.0, 0.0},
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

  memcpy(temp, transformation, 4 * 4 * sizeof(double));
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

  memcpy(temp, invTransformation, 4 * 4 * sizeof(double));
  mult(invTransformation, invRotation, temp);
}

void Transformer::setScale(double s[3])
{
  double temp[4][4] = {{0, 0, 0, 0},
		       {0.0, 0.0, 0.0, 0.0},
		       {0.0, 0.0, 0.0, 0.0},
		       {0, 0, 0, 0}};
  loadIdMatrix(scale);

  for (int i = 0; i < 3; i++)
    scale[i][i] = s[i];

  memcpy(temp, transformation, 4 * 4 * sizeof(double));
  mult(transformation, temp, scale);

  loadIdMatrix(invScale);

  for (int i = 0; i < 3; i++)
    invScale[i][i] = 1.0 / s[i];

  memcpy(temp, invTransformation,  4 * 4 * sizeof(double));
  mult(invTransformation, invScale, temp);
}

void Transformer::transform(double res[4],
			    double vec[4])
{
  mult(res, vec, transformation);
  if (res[3]!=0)
    for(int i = 0; i < 4; i++)
      res[i]/=res[3];
}

void Transformer::transformInv(double res[4],
			       double vec[4])
{
  mult(res, vec, invTransformation);
  if (res[3]!=0)
    for(int i = 0; i < 4; i++)
      res[i]/=res[3];
}

void Transformer::normalize(double p[4])
{
  double d = 0;

  for (int i = 0; i < 3; i++)
    d += p[i] * p[i];

  d = sqrt (d);
  for (int i = 0; i < 3; i++)
    p[i] /= d;
}
