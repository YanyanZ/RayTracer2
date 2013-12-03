# include <tools/ONB.hpp>

Tools::ONB::~ONB()
{
}

Tools::ONB::ONB()
{
}

Tools::ONB::ONB(const Vector<float> a, const Vector<float> b, 
		const Vector<float> c)
  : u (a), v (b), w (c)
{
}

void Tools::ONB::initFromU(const Vector<float>& _u)
{
  Vector<float> n = Vector<float>(1, 0, 0);
  Vector<float> m = Vector<float>(0, 1, 0);

  u = Vector<float>::unitVector(_u);
  v = Vector<float>::cross(u, n);

  if (v.length() < 0.01)
    v = Vector<float>::cross(u, m);
  
  w = Vector<float>::cross(u, v);
}

void Tools::ONB::initFromV(const Vector<float>& _v)
{
  Vector<float> n = Vector<float>(1, 0, 0);
  Vector<float> m = Vector<float>(0, 1, 0);

  u = Vector<float>::unitVector(_v);
  v = Vector<float>::cross(v, n);

  if (u.length() < 0.01)
    v = Vector<float>::cross(u, m);
  
  w = Vector<float>::cross(u, v);
}

void Tools::ONB::initFromW(const Vector<float>& _w)
{
  Vector<float> n = Vector<float>(1, 0, 0);
  Vector<float> m = Vector<float>(0, 1, 0);

  w = Vector<float>::unitVector(_w);
  v = Vector<float>::cross(w, n);

  if (u.length() < 0.01)
    u = Vector<float>::cross(w, m);
  
  w = Vector<float>::cross(w, u);
}

void Tools::ONB::initFromUV(const Vector<float>& _u, const Vector<float>& _v)
{
  u = Vector<float>::unitVector(_u);
  w = Vector<float>::unitVector(Vector<float>::cross(_u, _v));
  v = Vector<float>::cross(w, u);
}

void Tools::ONB::initFromVU(const Vector<float>& _v, const Vector<float>& _u)
{
  v = Vector<float>::unitVector(_v);
  w = Vector<float>::unitVector(Vector<float>::cross(_u, _v));
  u = Vector<float>::cross(v, w);
}

void Tools::ONB::initFromUW(const Vector<float>& _u, const Vector<float>& _w)
{
  u = Vector<float>::unitVector(_u);
  v = Vector<float>::unitVector(Vector<float>::cross(_w, _u));
  w = Vector<float>::cross(u, v);
}

void Tools::ONB::initFromWU(const Vector<float>& _w, const Vector<float>& _u)
{
  w = Vector<float>::unitVector(_w);
  v = Vector<float>::unitVector(Vector<float>::cross(_w, _u));
  u = Vector<float>::cross(v, w);
}

void Tools::ONB::initFromVW(const Vector<float>& _v, const Vector<float>& _w)
{
  v = Vector<float>::unitVector(_v);
  u = Vector<float>::unitVector(Vector<float>::cross(_v, _w));
  w = Vector<float>::cross(u, v);
}

void Tools::ONB::initFromWV(const Vector<float>& _w, const Vector<float>& _v)
{
  w = Vector<float>::unitVector(_w);
  u = Vector<float>::unitVector(Vector<float>::cross(_v, _w));
  v = Vector<float>::cross(w, u);
}
