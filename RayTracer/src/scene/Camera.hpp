#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <iostream>
# include <cmath>
# include <vector>

# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

using namespace Tools;

namespace Engine
{
  class Camera
  {
  public:
    enum {PERSPECTIVE, ORTHOGRAPHIC};

  private:
    double focal;
    std::vector<double> position;
    std::vector<double> lookAt;
    double fov;
    int tProjection;
    double sProjection;

  private:
    Transformer* trans;

  public:
    Camera (std::vector<double> pos, std::vector<double> lat);
    ~Camera(void);

  public:
    const double getFocal(void);
    const double getFov(void);
    const int getTProjection(void);
    const double getSProjection(void);

  public:
    void setTransformation();
    void setFocal(double f);
    void setFov(double f);
    void setTProjection (int tp);
    void setSProjection(double ps);

  public:
    void rScene(Ray* r, Ray *r2);
  };
}

#endif
