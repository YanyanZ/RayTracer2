#ifndef _ONB_HPP__
# define _ONB_HPP__

# include <tools/Vector.hpp>
# include <tools/Ray.hpp>

using namespace Tools;

namespace Tools
{
  class ONB
  {
  public:
    Vector<float> u;
    Vector<float> v;
    Vector<float> w;

  public:
    ~ONB();

  public:
    ONB();
    ONB(const Vector<float> a, const Vector<float> b, const Vector<float> c);

  public:
    void initFromU(const Vector<float>& _u);
    void initFromV(const Vector<float>& _v);
    void initFromW(const Vector<float>& _w);
    void initFromUV(const Vector<float>& _u, const Vector<float>& _v);
    void initFromVU(const Vector<float>& _v, const Vector<float>& _u);
    void initFromUW(const Vector<float>& _u, const Vector<float>& _w);
    void initFromWU(const Vector<float>& _w, const Vector<float>& _u);
    void initFromVW(const Vector<float>& _v, const Vector<float>& _W);
    void initFromWV(const Vector<float>& _w, const Vector<float>& _v);

  public:
    bool operator==(const ONB& onb);
    void set(const Vector<float> a, const Vector<float> b, const Vector<float> c);
  };
}

#endif
