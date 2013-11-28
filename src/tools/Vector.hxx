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
Vector<T> Tools::Vector<T>::operator=(const Vector& v)
{
  return (Vector<T>(v.x, v.y, v.z));
}

template <typename T>
bool Tools::Vector<T>::operator==(const Vector& v)
{
  return (v.x == x && v.y == y && v.z == z);
}

template <typename T>
bool Tools::Vector<T>::operator!=(const Vector& v)
{
  return (v.x != x || v.y != y || v.z != z);
}

template <typename T>
Vector<T> Tools::Vector<T>::operator+(const Vector& v)
{
  return (Vector<T>(v.x + x, v.y + y, v.z + z));
}

template <typename T>
Vector<T> Tools::Vector<T>::operator-(const Vector& v)
{
  return (Vector<T>(-v.x + x, -v.y + y, -v.z + z));
}

template <typename T>
Vector<T> Tools::Vector<T>::operator*(const Vector& v)
{
  return (Vector<T>(v.x * x, v.y * y, v.z * z));
}

template <typename T>
Vector<T> Tools::Vector<T>::operator*(const T& a)
{
  return (Vector<T>(a * x, a * y, a * z));
}

template <typename T>
Vector<T> Tools::Vector<T>::operator/(const T& a)
{
  return (Vector<T>(x / a, y / a, z / a));
}

template <typename T>
std::ostream& Tools::Vector<T>::operator<<(std::ostream& flux)
{
  flux << "x : " << x << " y : " << y << " z : " << z;
  return flux;
}

template <typename T>
T Tools::Vector<T>::getX() const
{
  return x;
}

template <typename T>
T Tools::Vector<T>::getY() const
{
  return y;
}

template <typename T>
T Tools::Vector<T>::getZ() const
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
  z = _z;
}

template <typename T>
T Tools::Vector<T>::minComponent() const
{
  if ((x < y) && (x < z))
    return x;
  else if ((y < x) && (y < z))
    return y;
  else if ((z < x) && (z < y))
    return z;
}

template <typename T>
T Tools::Vector<T>::maxComponent() const
{
  if ((x > y) && (x > z))
    return x;
  else if ((y > x) && (y > z))
    return y;
  else if ((z > x) && (z > y))
    return z;
}

template <typename T>
Vector<T> Tools::Vector<T>::cross(const Vector<T>& v1, const Vector<T>& v2)
{
  Vector<T> tmp;

  tmp.x = v1.y * v2.z - v1.z * v2.y;
  tmp.y = v1.z * v2.x - v1.x * v2.z;
  tmp.z = v1.x * v2.y - v1.y * v2.x;

  return tmp;
}

template <typename T>
T Tools::Vector<T>::dot(const Vector<T>& v1, const Vector<T>& v2)
{
  return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

template <typename T>
T Tools::Vector<T>::length() const
{
  return (sqrt(x * x + y * y + z * z));
}

template <typename T>
Vector<T> Tools::Vector<T>::unitVector(const Vector<T>& v)
{
  const T len = v.length();

  return (Vector<T>(v.x / len, v.y / len, v.z / len));
}
