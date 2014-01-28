# include <scene/Camera.hpp>

using namespace Engine;

Camera::Camera (std::vector<double> pos, std::vector<double> lat)
  : fov (60), sProjection (10)
{
  position = pos;
  lookAt = lat;
  setTransformation();
}

Camera::~Camera ()
{
}


void Camera::setFocal(double f)
{
  focal = f;
}

void Camera::setFov(double f)
{
  fov = f;
}

void Camera::setTProjection (int tp)
{
  tProjection = tp;
}

void Camera::setSProjection(double ps)
{
  sProjection = ps;
}

const int Camera::getTProjection(void)
{
  return tProjection;
}

const double Camera::getFocal(void)
{
  return sProjection / (2.0 * tan(fov / 2.0 * (M_PI / 180.0)));
}

const double Camera::getFov(void)
{
  return fov;
}


const double Camera::getSProjection(void)
{
  return sProjection;
}

void Camera::setTransformation(void)
{
  std::vector<double> rot = {0, 0, 0};
  std::vector<double> transla = {position[0], position[1], position[2]};
  std::vector<double> vlookAt = {0, 0, 0, 0};
  double theta;
  double d;

  trans = new Transformer();
  trans->setTranslation(transla);

  for (int i= 0; i < 4; i++)
    vlookAt[i] = lookAt[i] - position[i];
  rot[2] = 0;

  d = sqrt(vlookAt[1] * vlookAt[1] +
	   vlookAt[2] * vlookAt[2]);

  theta = acos(vlookAt[2] / d);
  if (vlookAt[1] < 0)
  	theta = -theta;
  rot[0] = theta;

  d = sqrt(vlookAt[0] * vlookAt[0]+
	   vlookAt[2] * vlookAt[2]);

  theta = acos(vlookAt[2] / d);
  if (vlookAt[0] < 0)
  	theta = -theta;
  rot[1] = theta;

  trans->setRotation(rot);
}

void Camera::rScene(Ray* r, Ray* r2)
{
  std::vector<double> dir = {0, 0, 0, 0};
  std::vector<double> pos = {0, 0, 0, 0};
  std::vector<double> dir2 = {0, 0, 0, 0};
  std::vector<double> pos2 = {0, 0, 0, 0};

  r->getOrigin(pos);
  r->getDirection(dir);

  trans->transform(pos2, pos);
  trans->transform(dir2, dir);

  r2->setOrigin(pos2);
  r2->setDirection(dir2);
  r2->setIn(r->isIn());
}
