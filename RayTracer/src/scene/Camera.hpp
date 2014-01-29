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
    double position[4];
    double lookAt[4];
    double fov;
    int tProjection;
    double sProjection;

  private:
    Transformer* trans;

  public:
    Camera (double pos[4], double lat[4]);
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
