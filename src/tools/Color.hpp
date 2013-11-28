#ifndef COLOR_HPP__
# define COLOR_HPP__

# include <iostream>

namespace Tools
{
  template <typename T>
  class RGBColor
  {
  public:
    T r;
    T g;
    T b;

  public:
    ~RGBColor();

  public:
    RGBColor();
    RGBColor(T a);
    RGBColor(T a, T bb, T c);

  public:
    bool operator==(const RGBColor& c);
    bool operator!=(const RGBColor& c);

  public:
    RGBColor<T> operator+(const RGBColor& c);
    RGBColor<T> operator-(const RGBColor& c);
    RGBColor<T> operator*(const RGBColor& c);
    RGBColor<T> operator*(const T a);

  public:
    std::ostream& operator<<(std::ostream& flux);
  };

  # include "Color.hxx"
}

#endif
