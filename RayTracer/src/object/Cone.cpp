# include <object/Cone.hpp>

using namespace Form;

Cone::Cone(double sr, double br, double h)
  : Object(), sRadius (sr), bRadius (br), heigh (h)
{
}

Cone::~Cone(void)
{
}

double Cone::hit(Ray* r, std::vector<double> i)
{
  double a, b, c, k, l, alpha, h;
  double delta;
  double t1, t2, t;
  double d;

  std::vector<double> p = {0, 0, 0, 0};
  std::vector<double> temp = {0, 0, 0, 0};
  std::vector<double> pos = {0, 0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  std::vector<double> pos2 = {0, 0, 0, 0};
  std::vector<double> dir2 = {0, 0, 0, 0};

  r->getOrigin(pos);
  r->getDirection(dir);

  trans->transformInv(pos2, pos);
  trans->transformInv(dir2, dir);

  alpha = atan(heigh / (bRadius - sRadius));
  h = heigh + sRadius * tan(alpha);
  k = (bRadius * bRadius) / (h * h);
  l = pos2[0] - h;

  a = dir2[1] * dir2[1] + dir2[2] * dir2[2] - k * dir2[0] * dir2[0];
  b = dir2[1] * pos2[1] + dir2[2] * pos2[2] - k * l * dir2[0];
  c = pos2[2] * pos2[2] + pos2[1] * pos2[1] - k * l * l;

  delta = b * b - a * c;

  if (delta < 0.0)
  {
    d = MAXDOUBLE;
  }
  else
  {
    t1 = (-b + sqrt (delta)) / a;
    t2 = (-b - sqrt (delta)) / a;

    if ((pos2[1] * pos2[1] + pos2[2] * pos2[2]) > (k * l * l))
    {
      if (t1 <= epsilon && t2 <= epsilon)
	d = MAXDOUBLE;
      else
      {
	if ((t1 <= t2 && t1 > epsilon) || (t2 < t1 && t2 < epsilon))
	  t = t1;
	else if ((t2 < t1 && t2 > epsilon) || (t1 < t2 && t1 < epsilon))
	  t = t2;

	p[0] = t * dir2[0] + pos2[0];
	p[1] = t * dir2[1] + pos2[1];
	p[2] = t * dir2[2] + pos2[2];
	p[3] = 1.0;
	d = distance (p, pos2);

	if (p[0] > heigh)
	{
	  t = (heigh - pos2[0]) / dir2[0];
	  p[0] = heigh;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon) && ((p[1] * p[1] + p[2] * p[2]) <=
				sRadius * sRadius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = MAXDOUBLE;
	}
	if (p[0] < 0.0)
	{
	  t = -pos2[0] / dir2[0];
	  p[0] = 0.0;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon) && ((p[1] * p[1] + p[2] * p[2]) <=
				bRadius * bRadius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = MAXDOUBLE;
	}
      }
    }
    else if ((pos2[1] * pos2[1] + pos2[2] * pos2[2]) <= (k * l * l)
	     && pos2[0] > h)
    {

      if (t1 < -epsilon || t2 < -epsilon ||
	  (t1 > t2 && t1 - t2 <= epsilon) || (t2 > t1
					      && t2 - t1 <= epsilon))
	d = MAXDOUBLE;
      else
      {
	if (t1 < t2)
	  t = t2;
	else
	  t = t1;
	p[0] = t * dir2[0] + pos2[0];
	p[1] = t * dir2[1] + pos2[1];
	p[2] = t * dir2[2] + pos2[2];
	p[3] = 1.0;
	d = distance (p, pos2);

	if (p[0] > heigh)
	{
	  t = (heigh - pos2[0]) / dir2[0];
	  p[0] = heigh;
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;

	  if ((t > epsilon) && ((p[1] * p[1] + p[2] * p[2]) <=
				sRadius * sRadius))
	  {
	    d = distance (p, pos2);
	  }
	  else
	    d = MAXDOUBLE;
	}

	if (p[0] < 0.0)
	{
	  d = MAXDOUBLE;
	}
      }
    }
    else if ((pos2[1] * pos2[1] + pos2[2] * pos2[2]) <= (k * l * l)
	     && pos2[0] <= h)
    {
      if (pos2[0] > heigh)
      {
	t = (heigh - pos2[0]) / dir2[0];
	p[0] = heigh;
	p[1] = t * dir2[1] + pos2[1];
	p[2] = t * dir2[2] + pos2[2];
	p[3] = 1.0;

	if ((t > epsilon) && ((p[1] * p[1] + p[2] * p[2]) <=
			      sRadius * sRadius))
	{
	  d = distance (p, pos2);
	}
	else
	  d = MAXDOUBLE;
      }
      else if (pos2[0] < 0.0)
      {
	t = -pos2[0] / dir2[0];
	p[0] = 0.0;
	p[1] = t * dir2[1] + pos2[1];
	p[2] = t * dir2[2] + pos2[2];
	p[3] = 1.0;

	if ((t > epsilon) && ((p[1] * p[1] + p[2] * p[2]) <=
			      bRadius * bRadius))
	{
	  d = distance (p, pos2);
	}
	else
	  d = MAXDOUBLE;
      }
      else
      {
	if (t1 <= epsilon && t2 <= epsilon)
	{
	  d = MAXDOUBLE;

	  if (pos2[0] > heigh)
	  {
	    t = (heigh - pos2[0]) / dir2[0];
	    p[0] = heigh;
	    p[1] = t * dir2[1] + pos2[1];
	    p[2] = t * dir2[2] + pos2[2];
	    p[3] = 1.0;

	    if ((t > epsilon) && ((p[1] * p[1] + p[2] * p[2]) <=
				  sRadius * sRadius))
	    {
	      d = distance (p, pos2);
	    }
	    else
	      d = MAXDOUBLE;
	  }
	  else
	  {
	    t = -pos2[0] / dir2[0];
	    p[0] = 0.0;
	    p[1] = t * dir2[1] + pos2[1];
	    p[2] = t * dir2[2] + pos2[2];
	    p[3] = 1.0;

	    if ((t > epsilon) && ((p[1] * p[1] + p[2] * p[2]) <=
				  bRadius * bRadius))
	    {
	      d = distance (p, pos2);
	    }
	    else
	      d = MAXDOUBLE;
	  }
	}
	else
	{
	  if ((t1 <= t2 && t1 > epsilon) || (t2 < t1 && t2 < epsilon))
	    t = t1;
	  else if ((t2 < t1 && t2 > epsilon) || (t1 < t2 && t1 < epsilon))
	    t = t2;

	  p[0] = t * dir2[0] + pos2[0];
	  p[1] = t * dir2[1] + pos2[1];
	  p[2] = t * dir2[2] + pos2[2];
	  p[3] = 1.0;
	  d = distance (p, pos2);

	  if (p[0] > heigh)
	  {
	    t = (heigh - pos2[0]) / dir2[0];
	    p[0] = heigh;
	    p[1] = t * dir2[1] + pos2[1];
	    p[2] = t * dir2[2] + pos2[2];
	    p[3] = 1.0;

	    if ((t > epsilon) && ((p[1] * p[1] + p[2] * p[2]) <=
				  sRadius * sRadius))
	    {
	      d = distance (p, pos2);
	    }
	    else
	      d = MAXDOUBLE;
	  }
	  if (p[0] < 0.0)
	  {
	    t = -pos2[0] / dir2[0];
	    p[0] = 0.0;
	    p[1] = t * dir2[1] + pos2[1];
	    p[2] = t * dir2[2] + pos2[2];
	    p[3] = 1.0;

	    if ((t > epsilon) && ((p[1] * p[1] + p[2] * p[2]) <=
				  bRadius * bRadius))
	    {
	      d = distance (p, pos2);
	    }
	    else
	      d = MAXDOUBLE;
	  }
	}
      }
    }

    trans->transform(i, p);
  }

  return d;
}

void Cone::normal(std::vector<double> p, Ray* r,
		  std::vector<double> normal)
{
  double d, alpha, beta;
  std::vector<double> p2 = {0, 0, 0, 0};
  std::vector<double> temp = {0, 0, 0, 0};

  trans->transformInv(p2, p);
  if ((p2[0] >= epsilon) && (p2[0] <= heigh - epsilon))
  {
    alpha = atan (heigh / (bRadius - sRadius));
    if (p2[1] == 0.0)
    {
      beta = M_PI_2;
      if (p2[2] < 0.0)
	beta = -beta;
    }
    else
      beta = atan (p2[2] / p2[1]);

    normal[0] = sin (M_PI_2 - alpha);

    if (p2[1] > 0)
    {
      normal[1] = (cos (beta)) * (cos (M_PI_2 - alpha));
      normal[2] = (sin (beta)) * (cos (M_PI_2 - alpha));
    }
    else
    {
      normal[1] = (cos (M_PI + beta)) * (cos (M_PI_2 - alpha));
      normal[2] = (sin (M_PI + beta)) * (cos (M_PI_2 - alpha));
    }
    normal[3] = 0;
  }
  else if (p2[0] < epsilon && (p2[0] > -epsilon))
  {
    normal[0] = -1.0;
    normal[1] = 0.0;
    normal[2] = 0.0;
    normal[3] = 0.0;
  }
  else if (p2[0] < (heigh + epsilon) && p2[0] > (heigh - epsilon))
  {
    normal[0] = 1.0;
    normal[1] = 0.0;
    normal[2] = 0.0;
    normal[3] = 0.0;
  }

  checkNormal (normal, p2, r);
}
