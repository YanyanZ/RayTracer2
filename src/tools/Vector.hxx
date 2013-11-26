template <typename T>
Tools::Vector<T>::~Vector()
{
}

Tools::Vector<T>::Vector() : x (0), y (0), z (0)
{
}

Tools::Vector<T>::Vector(T a) : x (a), y (a), z (a)
{
}

Tools::Vector<T>::Vector(T a, T b, T c)
  : x (a), y (b), z (c)
{
}

bool Tools::Vector<T>operator==(const Vector& v)
{
  return (v.x == x && v.y == y && v.z == z);
}

bool Tools::Vector<T>::operator!=(const Vector& v)
{
  return (v.x != x || v.y != y || v.z != z);
}

Vector Tools::Vector<T>::operator+(const Vector& v)
{
  return (Vector(v.x + x, v.y + y, v.z + z));
}

Vector Tools::Vector<T>::operator-(const Vector& v)
{
  return (Vector(-v.x + x, -v.y + y, -v.z + z));
}

Vector Tools::Vector<T>::opeartor*(const Vector& v)
{
  return (Vector(v.x * x, v.y * y, v.z * z));
}

Vector Tools::Vector<T>::operator*(const T& a)
{
  return (Vector(a * x, a * y, a * z));
}

std::ostream& Tools:::Vector<T>::operator<<(std::ostream& flux, Vector const& v)
{
  flux << "x : " << x << " y : " << y << " z : " << z;
  return flux;
}

