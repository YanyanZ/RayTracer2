#ifndef VECTOR_HPP__
# define VECTOR_HPP__

namespace Tools
{
  template <typename T>
  class Vector
  {
  private:
    T x;
    T y;
    T z;

  public:p
    ~Vector();

  public:
    Vector();
    Vector(T a);
    Vector(T a, T b, T c);

  public:
    T x() const;
    T y() const;
    T z() const;

  public:
    void setX(T _x);
    void setY(T _y);
    void setZ(T _z);

  public:
    T minComponent() const;
    T maxComponent() const;
    T minAbsComponent() const;
    T maxAbsComponent() const;

  public:
    Vector operator=(const std::vector<T> v);
    float operator[](int i) const;
    Vector operator-() const;

  public:
    bool operator==(const Vector& v);
    bool operator!=(const Vector& v);    

  public:
    Vector operator+(const Vector& v);
    Vector operator-(const Vector& v);
    Vector operator*(const Vector& v);
    Vector operator*(const T& a);

  public:
    Vector operator+=(const Vector& v);
    Vector operator-=(const Vector& v);
    Vector operator*=(const Vector& v);
    Vector operator*=(const T& a);

  public:
    std::ostream& operator<<(std::ostream& flux, Vector const& v);
  };

  # incude "Vector.hxx"

}

#endif
