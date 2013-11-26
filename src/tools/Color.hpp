#ifndef COLOR_HPP__
# define COLOR_HPP__

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
    RGBColor operator+(const RGBColor& c);
    RGBColor operator-(const RGBColor& c);
    RGBColor operator*(const RGBColor& c);
    RGBColor operator*(const T& a);

  public:
    std::ostream& operator<<(std::ostream& flux, Vector const&v);
  };

  # include "RGBColor.hxx"
}

#endif
