template <typename T>
Tools::RGBColor<T>::~RGBColor()
{
}

template <typename T>
Tools::RGBColor<T>::RGBColor() : r (0), g (0), b (0)
{
}

template <typename T>
Tools::RGBColor<T>::RGBColor(T a) : r (a), g (a), b (a)
{
}

template <typename T>
Tools::RGBColor<T>::RGBColor(T a, T bb, T c) : r (a),  g (bb), b (a)
{
}

template <typename T>
bool Tools::RGBColor<T>::operator==(const RGBColor& c)
{
  return (c.r == r && c.g == g && c.b == b);
}

template <typename T>
bool Tools::RGBColor<T>::operator!=(const RGBColor& c)
{
  return (c.r != r && c.g != g && c.b != b);
}

template <typename T>
RGBColor Tools::RGBColor<T>::operator+(const RGBColor& c)
{
  return (RGBColor(c.r + r, c.g + g, c.b + b));
}

template <typename T>
RGBColor Tools::RGBColor<T>::operator-(const RGBColor& c)
{
  return (RGBColor(-c.r + r, -c.g + g, -c.b + b));
}

template <typename T>
RGBColor Tools::RGBColor<T>::operator*(const RGBColor& c)
{
  return (RGBColor(c.r * r, c.g * g, c.b * b));
}

template <typename T>
RGBColor Tools::RGBColor<T>::operator*(const T a)
{
  return (RGBColor(a * r, a * g, a * b));
}

template <typename T>
std::ostream& Tools::RGBColor<T>::operator<<(std::ostream& flux, Vector const&v)
{
  flux << "Red: " << r << " Green: " << g << " Blue: " << b;
  return flux;
}
