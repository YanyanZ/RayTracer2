#ifndef SCENE_HPP
# define SCENE_HPP

# include <cstdlib>
# include <vector>

# include <object/Object.hpp>
# include <scene/Camera.hpp>
# include <scene/Background.hpp>

# include <light/Ambiant.hpp>
# include <light/Point.hpp>
# include <light/Directional.hpp>

using namespace Tools;
using namespace Lightning;

namespace Engine
{
  class Scene
  {
  private:
    std::vector<Object*>* objects;
    std::vector<Directional*>* dLights;
    std::vector<Point*>* pLights;
    std::vector<double> cBackground;
    Ambiant* aLight;
    Camera* cam;

  private:
    int nbDirectional;
    int nbPoint;
    int nbObject;
    int maxTraceLevel;
    int antialiasing;
    double aaThreshold;
    int oHeight;
    int oWidth;
    double softShadow;
    bool modeSoftShadow;
    int nbShadowRay;

  public:
    Scene(void);
    virtual ~Scene(void);

  public:
    void addObject(Object* o);
    void changeCamera(Camera* c);
    void addAmbiant(Ambiant* l);
    void addDirectional(Directional* l);
    void addPoint(Point* l);

  public:
    bool isPointRadiance(std::vector<double> p, int nlum);
    bool isDirectionalRadiance(std::vector<double> p, int nlum);

  public:
    Camera* getCamera(void);
    Object* getObject(int i);
    Point* getPoint(int i);
    Directional* getDirectional(int i);
    const int getNbObjects(void);
    const int getNbPoints(void);
    const int getNbDirectionals(void);
    void getAmbiant(std::vector<double> amb);
    const int getNbShadowRay(void);
    const int getMaxTraceLevel(void);
    const int getAntialiasing(void);
    const double getAAThreshold(void);
    const int getOutputHeight(void);
    const int getOutputWidth(void);
    const std::vector<double> getBackground(void);

  public:
    void setBackground(std::vector<double> c);
    void setGlobalSetting(int mtl, int antil,  double aath,
			  double ss, int nbss, int oh, int ow);
  };
}

#endif
