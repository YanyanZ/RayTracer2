#ifndef VECTOR_HPP__
# define VECTOR_HPP__

# include <iostream>
# include <cmath>

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
    T getX() const;
    T getY() const;
    T getZ() const;

  public:
    void setX(T _x);
    void setY(T _y);
    void setZ(T _z);

  public:
    T length() const;
    T minComponent() const;
    T maxComponent() const;
    T minAbsComponent() const;
    T maxAbsComponent() const;

  public:
    Vector<T> operator=(const Vector& v);
    float operator[](int i) const;
    Vector<T> operator-() const;

  public:
    bool operator==(const Vector& v);
    bool operator!=(const Vector& v);    

  public:
    Vector<T> operator+(const Vector& v);
    Vector<T> operator-(const Vector& v);
    Vector<T> operator*(const Vector& v);
    Vector<T> operator*(const T& a);

  public:
    Vector<T> operator+=(const Vector& v);
    Vector<T> operator-=(const Vector& v);
    Vector<T> operator*=(const Vector& v);
    Vector<T> operator*=(const T& a);

  public:
    Vector<T> operator/(const T& a);

  public:
    std::ostream& operator<<(std::ostream& flux);

  public:
    static Vector<T> cross(const Vector<T>& v1, const Vector<T>& v2);
    static T dot(const Vector<T>& v1, const Vector<T>& v2);
    static Vector<T> unitVector(const Vector<T>& v);
  };

  # include "Vector.hxx"

}

using namespace Tools;

template <typename T>
bool operator==(const Vector<T>& v1, const Vector<T>& v2)
{
  return ((v1.x == v2.x) && (v1.y == v2.y) && (v1.z == v2.z));
}

template <typename T>
bool operator!=(const Vector<T>& v1, const Vector<T>& v2)
{
  return ((v1.x != v2.x) && (v1.y != v2.y) && (v1.z != v2.z));
}

template <typename T>
Vector<T> operator+(const Vector<T>& v1, const Vector<T>& v2)
{
  return (Vector<T>(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

template <typename T>
Vector<T> operator-(const Vector<T>& v1, const Vector<T>& v2)
{
  return (Vector<T>(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

template <typename T>
Vector<T> operator*(const Vector<T>& v1, const Vector<T>& v2)
{
  return (Vector<T>(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}

template <typename T>
Vector<T> operator*(const T& a, const Vector<T>& v)
{
  return (Vector<T>(v.x * a, v.y * a, v.z * a));
}

template <typename T>
Vector<T> operator*(const Vector<T>& v, const T& a)
{
  return (Vector<T>(v.x * a, v.y * a, v.z * a));
}

template <typename T>
Vector<T> operator/(const T& a, const Vector<T>& v)
{
  return (Vector<T>(a / v.x, a / v.y, a / v.z));
}

template <typename T>
Vector<T> operator/(const Vector<T>& v, const T& a)
{
  return (Vector<T>(v.x / a, v.y / a, v.z / a));
}

template <typename T>
std::ostream& operator<<(std::ostream& flux, const Vector<T>& v)
{
  flux << v.x << ";" << v.y << ";" << v.z;
  return flux;
}

#endif
