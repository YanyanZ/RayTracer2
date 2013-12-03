#ifndef CAMERA_HPP__
# define CAMERA_HPP__

# include <tools/ONB.hpp>
# include <tools/Vector.hpp>
# include <tools/Ray.hpp>

using namespace Tools;

class Camera
{
public:
  Vector<float> center, corner, across, up;
  ONB uvw;
  float lens_radius;
  float u0, u1, v0, v1;
  float d;

public:
  ~Camera();

public:
  Camera();
  Camera(const Camera& orig);
  Camera(Vector<float> c, Vector<float> gaze, Vector<float> vup, float aperture,
	 float left, float right, float bottom, float top, float distance);
 
public:
  Ray getRay(float a, float b, float xi1, float xi2);
};

#endif
