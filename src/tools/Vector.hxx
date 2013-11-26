template <typename T>
Tools::Vector<T>::~Vector()
{
}

template <typename T>
Tools::Vector<T>::Vector() : x (0), y (0), z (0)
{
}

template <typename T>
Tools::Vector<T>::Vector(T a) : x (a), y (a), z (a)
{
}

template <typename T>
Tools::Vector<T>::Vector(T a, T b, T c)
  : x (a), y (b), z (c)
{
}

template <typename T>
bool Tools::Vector<T>operator==(const Vector& v)
{
  return (v.x == x && v.y == y && v.z == z);
}

template <typename T>
bool Tools::Vector<T>::operator!=(const Vector& v)
{
  return (v.x != x || v.y != y || v.z != z);
}

template <typename T>
Vector Tools::Vector<T>::operator+(const Vector& v)
{
  return (Vector(v.x + x, v.y + y, v.z + z));
}

template <typename T>
Vector Tools::Vector<T>::operator-(const Vector& v)
{
  return (Vector(-v.x + x, -v.y + y, -v.z + z));
}

template <typename T>
Vector Tools::Vector<T>::opeartor*(const Vector& v)
{
  return (Vector(v.x * x, v.y * y, v.z * z));
}

template <typename T>
Vector Tools::Vector<T>::operator*(const T& a)
{
  return (Vector(a * x, a * y, a * z));
}

template <typename T>
std::ostream& Tools:::Vector<T>::operator<<(std::ostream& flux, Vector const& v)
{
  flux << "x : " << x << " y : " << y << " z : " << z;
  return flux;
}

template <typename T>
T Tools::Vector<T>::x() const
{
  return x;
}

template <typename T>
T Tools::Vector<T>::y() const
{
  return y;
}

template <typename T>
T Tools::Vector<T>::z() const
{
  return z;
}

template <typename T>
void Tools::Vector<T>::setX(T _x)
{
  x = _x;
}

template <typename T>
void Tools::Vector<T>::setY(T _y)
{
  y = _y;
}

template <typename T>
void Tools::Vector<T>::setZ(T _z)
{
  z = z_;
}

template <typename T>
T Tools::minComponent() const
{
  if ((x < y) && (x < z))
    return x;
  else if ((y < x) && (y < z))
    return y;
  else if ((z < x) && (z < y))
    return z;
}

template <typename T>
T Tools::maxComponent() const
{
  if ((x > y) && (x > z))
    return x;
  else if ((y > x) && (y > z))
    return y;
  else if ((z > x) && (z > y))
    return z;
}
