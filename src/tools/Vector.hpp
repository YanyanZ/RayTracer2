#ifndef VECTOR_HPP__
# define VECTOR_HPP__

namespace Tools
{
  template <typename T>
  class Vector
  {
  public:
    T x;
    T y;
    T z;

  public:
    ~Vector();

  public:
    Vector();
    Vector(T a);
    Vector(T a, T b, T c);

  public:
    bool operator==(const Vector& v);
    bool operator!=(const Vector& v);
    
  public:
    Vector operator+(const Vector& v);
    Vector operator-(const Vector& v);
    Vector operator*(const Vector& v);
    Vector operator*(const T& a);

  public:
    std::ostream& operator<<(std::ostream& flux, Vector const& v);
  };

  # incude "Vector.hxx"

}

#endif
