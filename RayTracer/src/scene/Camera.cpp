# include <scene/Camera.hpp>

using namespace Engine;

Camera::Camera (double pos[4], double lat[4])
  : fov (60), sProjection (10)
{
  memcpy(position, pos, 4 * sizeof(double));
  memcpy(lookAt, lat, 4 * sizeof(double));

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
  double rot[3];
  double transla[3];
  double vlookAt[4];
  double theta;
  double d;

  transla[0] = position[0];
  transla[1] = position[1];
  transla[2] = position[2];

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
  double dir[4] = {0, 0, 0, 0};
  double pos[4] = {0, 0, 0, 0};
  double dir2[4] = {0, 0, 0, 0};
  double pos2[4] = {0, 0, 0, 0};

  r->getOrigin(pos);
  r->getDirection(dir);

  trans->transform(pos2, pos);
  trans->transform(dir2, dir);

  r2->setOrigin(pos2);
  r2->setDirection(dir2);
  r2->setIn(r->isIn());
}
