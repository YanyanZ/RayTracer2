# include <objects/basic/Triangle.hpp>

Objects::Basic::Triangle::~Triangle()
{
}

Objects::Basic::Triangle::Triangle(const Vector<float> _s0,
				   const Vector<float> _s1,
				   const Vector<float> _s2,
				   const RGBColor<float> rgb)
  : s0 (_s0), s1 (_s1), s2 (_s2), color (rgb)
{
}

bool Objects::Basic::Triangle::hit(const Ray& r, float tmin, float tmax, float time,
				    HitRecord& hr)
{
  float tval;
  float A = s0.x - s1.x;
  float B = s0.y - s1.y;
  float C = s0.z - s1.z;

  float D = s0.x - s2.x;
  float E = s0.y - s2.y;
  float F = s0.z - s2.z;

  float G = r.direction().x;
  float H = r.direction().y;
  float I = r.direction().z;

  float J = s0.x - r.origin().x;
  float K = s0.y - r.origin().y;
  float L = s0.z - r.origin().z;

  float EIHF = E * I - H * F;
  float GFDI = G * F - D * I;
  float DHEG = D * H - E * G;

  float denom = (A * EIHF  + B * GFDI + C * DHEG);
  float beta = (J * EIHF + K * GFDI + L * DHEG) / denom;

  if (beta <= 0.0 || beta >= 1)
    return false;

  float AKJB = A * K - J * B;
  float JCAL = J * C - A * L;
  float BLKC = B * L - K * C;

  float gamma = (I * AKJB + H * JCAL + G * BLKC) / denom;

  if (gamma <= 0.0 || beta + gamma >= 1)
    return false;

  tval = -(F * AKJB + E * JCAL + D * BLKC) / denom;

  if (tval >= tmin && tval <= tmax)
  {
    hr.t = tval;
    hr.normal = Tools::Vector<float>::unitVector(Tools::Vector<float>::cross((s1 - s0), (s2 - s0)));
    hr.color = color;
    return true;
  }

  return false;
}

bool Objects::Basic::Triangle::shadowHit(const Ray& r, float tmin, float tmax, float time)
{
  float tval;
  float A = s0.x - s1.x;
  float B = s0.y - s1.y;
  float C = s0.z - s1.z;

  float D = s0.x - s2.x;
  float E = s0.y - s2.y;
  float F = s0.z - s2.z;

  float G = r.direction().x;
  float H = r.direction().y;
  float I = r.direction().z;

  float J = s0.x - r.origin().x;
  float K = s0.y - r.origin().y;
  float L = s0.z - r.origin().z;

  float EIHF = E * I - H * F;
  float GFDI = G * F - D * I;
  float DHEG = D * H - E * G;

  float denom = (A * EIHF  + B * GFDI + C * DHEG);
  float beta = (J * EIHF + K * GFDI + L * DHEG) / denom;

  if (beta <= 0.0 || beta >= 1)
    return false;

  float AKJB = A * K - J * B;
  float JCAL = J * C - A * L;
  float BLKC = B * L - K * C;

  float gamma = (I * AKJB + H * JCAL + G * BLKC) / denom;

  if (gamma <= 0.0 || beta + gamma >= 1)
    return false;

  tval = -(F * AKJB + E * JCAL + D * BLKC) / denom;

  return (tval >= tmin && tval <= tmax);
}
