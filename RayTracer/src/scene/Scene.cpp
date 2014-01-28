# include <scene/Scene.hpp>

using namespace Engine;

Scene::Scene ()
  : nbDirectional (0),
    nbPoint (0),
    nbObject (0)
{
  objects = new std::vector<Object*>();
  dLights = new std::vector<Directional*>();
  pLights = new std::vector<Point*>();
  aLight = nullptr;
  cam = nullptr;
}

Scene::~Scene ()
{
  if (objects)
    delete objects;

  if (dLights)
    delete dLights;

  if (pLights)
    delete pLights;

  if (aLight)
    delete aLight;

  if (cam)
    delete cam;
}

void Scene::addObject(Object* o)
{
  objects->push_back(o);
  nbObject++;
}

void Scene::addDirectional(Directional* l)
{
  dLights->push_back(l);
  nbDirectional++;
}

void Scene::addPoint(Point* l)
{
  pLights->push_back(l);
  nbPoint++;
}

void Scene::addAmbiant(Ambiant* l)
{
  aLight = l;
}

void Scene::changeCamera(Camera* c)
{
  cam = c;
}

Camera* Scene::getCamera(void)
{
  return cam;
}

Object* Scene::getObject(int i)
{
  return (*objects)[i];
}

Point* Scene::getPoint(int i)
{
  return (*pLights)[i];
}

Directional* Scene::getDirectional(int i)
{
  return (*dLights)[i];
}

bool Scene::isPointRadiance(std::vector<double> p, int nlum)
{
  int i;
  bool radiance = true;
  double d;

  std::vector<double> pos = {0, 0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  std::vector<double> p2 = {0, 0, 0, 0};

  Ray* r = new Ray();
  double dLum;

  for (int j = 0; j < 4; j++)
    p[j] /= p[3];

  r->setOrigin(p);

  (*pLights)[nlum]->getPosition (pos);

  if (modeSoftShadow)
    for(int j = 0; j < 3; j++)
      pos[j] += static_cast<double>(random()) /
	(static_cast<double>(MAXINT) / softShadow) - softShadow / 2.0;

  for (int j = 0; j < 3; j++)
    dir[j] = pos[j] - p[j];
  dir[3]=0;

  r->setDirection(dir);

  for (int i = 0; i < 4; i++)
  {
    p[i] = p[i] / p[3];
    pos[i] = pos[i] / pos[3];
  }
  dLum = 0;

  for (int i = 0; i < 3; i++)
    dLum += (p[i] - pos[i]) * (p[i] - pos[i]);
  dLum = sqrt (dLum);

  i = 0;
  while (radiance && i < nbObject)
  {
    d = (*objects)[i]->hit(r, p2);

      if (d < dLum && d>0.001 )
	radiance = false;
      i++;
  }

  return radiance;
}

bool
Scene::isDirectionalRadiance(std::vector<double> p,
			     int nlum)
{
  int i;
  bool radiance = true;
  double d;
  std::vector<double> p2 = {0, 0, 0, 0};
  std::vector<double> dir = {0, 0, 0, 0};
  Ray* r = new Ray();

  for (int j = 0; j < 4; j++)
    p[j] /= p[3];

  r->setOrigin(p);

  (*dLights)[nlum]->getDirection(dir);
  for(int i = 0; i < 3; i++)
    dir[i] = -dir[i];

  if (modeSoftShadow)
  {
    for(int j = 0; j < 3; j++)
      dir[j] +=	static_cast<double>(random()) /
	(static_cast<double>(MAXINT) / softShadow) - softShadow / 2.0;
    r->setDirection(dir);
  }
  else
    r->setDirection(dir);

  i = 0;
  while (radiance && i < nbObject)
  {
    d = (*objects)[i]->hit(r, p2);
    if (d < MAXDOUBLE && d > 0.001)
      radiance = false;
    i++;
  }

  return radiance;
}

const int Scene::getNbObjects(void)
{
  return nbObject;
}

const int Scene::getNbPoints(void)
{
  return nbPoint;
}

const int Scene::getNbDirectionals(void)
{
  return nbDirectional;
}

void Scene::getAmbiant(std::vector<double> lumAmb)
{
  aLight->getColor(lumAmb);
}

void Scene::setBackground (std::vector<double> c)
{
  cBackground = c;
}

void Scene::setGlobalSetting (int mtl, int antil,  double aath,
			      double ss, int nbss, int oh, int ow)
{
  maxTraceLevel = mtl;
  antialiasing = antil;
  aaThreshold = aath;
  softShadow = ss;
  nbShadowRay = nbss;
  oHeight = oh;
  oWidth = ow;

  if (softShadow == -1)
    modeSoftShadow = false;
  else
    modeSoftShadow = true;
}

const int Scene::getMaxTraceLevel(void)
{
  return maxTraceLevel;
}

const int Scene::getAntialiasing(void)
{
  return antialiasing;
}

const double Scene::getAAThreshold (void)
{
  return aaThreshold;
}

const int Scene::getOutputHeight (void)
{
  return oHeight;
}

const int Scene::getOutputWidth(void)
{
  return oWidth;
}

const std::vector<double> Scene::getBackground(void)
{
  return cBackground;
}

const int Scene::getNbShadowRay(void)
{
  return nbShadowRay;
}
