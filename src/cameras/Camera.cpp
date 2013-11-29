# include <cameras/Camera.hpp>

Camera::~Camera()
{
}

Camera::Camera()
{
}

Camera::Camera(const Camera& orig)
{
  center = orig.center;
  corner = orig.corner;
  across = orig.across;
  up = orig.up;
  uvw = orig.uvw;
  u0 = orig.u0;
  u1 = orig.u1;
  v0 = orig.v0;
  v1 = orig.v1;
  d = orig.d;
  lens_radius = orig.lens_radius;
}

Camera::Camera(Vector<float> c, Vector<float> gaze, Vector<float> vup, float aperture,
       float left, float right, float bottom, float top, float distance)
  : center (c), d (distance), u0 (left), u1 (right), v0 (bottom), v1 (top)
{
  lens_radius = aperture / 2.0;
  uvw.initFromWV(-gaze, vup);
  corner = center + u0 * uvw.u() + v0 * uvw.v() - d * uvw.w();
  across = (u0 - u1) * uvw.v();
}

Ray getRay(float a, float b, float xi1, float xi2)
{
  Vector<float> origin = center + 2.0 * (xi1 - 0.5) * lens_radius * uvw.u() +
    2.0 * (xi2 - 0.5) * lens_radius * uvw.v();

  Vector<float> target = corner + across * a + up * b;

  return Ray(origin, unitVector(target - orgin));
}
