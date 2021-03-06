# include <object/Object.hpp>

using namespace Form;

Object::Object(void)
  : epsilon (0.001),
    rhoA (0.5),
    rhoD (0.5),
    rhoS (0.5),
    rhoR (0.5),
    rhoT (0.5),
    n (1),
    shiness (1),
    tPigment (COLOR),
    tNormal (NO),
    mapper (nullptr)
{
}

Object::~Object (void)
{
  c[0] = 1;
  c[1] = 1;
  c[2] = 1;
}

void Object::setEpsilon (double e)
{
  epsilon = e;
}


void Object::setRhoA(double v)
{
  rhoA = v;
}

void Object::setRhoD(double v)
{
  rhoD = v;
}

void Object::setRhoS(double v)
{
  rhoS = v;
}

void Object::setRhoT(double v)
{
  rhoT = v;
}

void Object::setRhoR(double v)
{
  rhoR = v;
}

void Object::setN(double v)
{
  n = v;
}

void Object::setShininess(double v)
{
  shiness = v;
}

void Object::setTypePigment(int t)
{
  tPigment = t;
}

void Object::setTypeNormal(int type)
{
  tNormal = type;
}

double Object::getRhoT(void)
{
  return rhoT;
}

double Object::getRefractionIndex(void)
{
  return n;
}

double Object::getEpsilon(void)
{
  return epsilon;
}

double Object::getRhoA(void)
{
  return rhoA;
}

double Object::getRhoD(void)
{
  return rhoD;
}

double Object::getRhoS(void)
{
  return rhoS;
}

double Object::getRhoR(void)
{
  return rhoR;
}

double
Object::getN(void)
{
  return n;
}

double Object::getShininess(void)
{
  return shiness;
}

double Object::distance(double* p1,
			double* p2)
{
  double d;

  for (int i = 0; i < 4; i++)
  {
    p1[i] = p1[i] / p1[3];
    p2[i] = p2[i] / p2[3];
  }

  d = 0;
  for (int i = 0; i < 3; i++)
    d += (p2[i] - p1[i]) * (p2[i] - p1[i]);

  d = sqrt (d);

  return d;
}

void Object::setTransformer (Transformer * trs)
{
  trans = trs;
}

bool Object::tRay(Ray* r,
		  double i[4],
		  double normal[4],
		  Ray* r2)
{
  double dev;
  double thetat, thetai;
  double coef;
  double ps;
  double dir[4];

  if (rhoT == 0)
    return false;
  else
  {
    r2->setOrigin(i);

    if (n == 1.0)
      r2->setIn(false);
    else
      r2->swapInOut();

    if (r->isIn())
      dev = n;
    else
      dev = 1.0 / n;

    trans->normalize(normal);
    ps = r->dot(normal);
    thetai = acos (ps);
    thetat = asin (dev * sin (thetai));
    coef = cos (thetat) + dev * ps;

    r->getDirection(dir);
    for (int ii = 0; ii < 3; ii++)
      dir[ii] = dev * dir[ii] - coef * normal[ii];
    dir[3] = 0;

    r2->setDirection(dir);

    return true;
  }
}

bool Object::rRay (Ray* r,
		   double i[4],
		   double normal[4],
		   Ray* r2)
{
  double dir[4];

  if (rhoR == 0)
    return false;
  else
  {
    r2->setOrigin(i);
    r2->setIn(r->isIn());

    r->getDirection(dir);
    for (int j = 0; j < 3; j++)
      dir[j]= dir[j] - 2 * r->dot(normal) * normal[j];
    dir[3]=0;

    r2->setDirection(dir);

    return true;
  }
}

double Object::hit(Ray* r, double i[4])
{
  return MAXDOUBLE;
}

void Object::normal(double p[4], Ray* r,
		    double normal[4])
{
}

void Object::setColor(double colo[3])
{
  memcpy(c, colo, 3 * sizeof(double));
}

void Object::setMapper (Mapper* mp)
{
  mapper = mp;
}

void Object::setChecker (Checker* cc)
{
  ccr = cc;
}

void Object::getColor (double p[4],
		       double* colo)
{
  double p2[4];

  switch (tPigment)
  {
    case COLOR:
      for (int i = 0; i < 3; i++)
	colo[i] = (1 - rhoT) * c[i];
      break;
    case CHECKER:
      ccr->getChecker(p, colo);
      break;
    case TEXTURE:
      trans->transformInv(p2, p);
      //mapper->getMapping(p2, colo);
      break;
    default:
      break;
    }
}

void Object::checkNormal(double n[4],
			 double p[4],
			 Ray* r)
{
  double temp[4];
  double rd[4];
  double tmp[4];
  double ps;

  r->getDirection(tmp);
  trans->transformInv(rd,tmp);

  ps = 0;
  for (int i = 0; i < 3; i++)
    ps += n[i] * rd[i];

  if (ps > 0.0)
    {
      temp[0] = -n[0];
      temp[1] = -n[1];
      temp[2] = -n[2];
      temp[3] = 0;
    }
  else
    {
      temp[0] = n[0];
      temp[1] = n[1];
      temp[2] = n[2];
      temp[3] = 0;
    }

  trans->transform(n, temp);
  trans->normalize(n);
}
