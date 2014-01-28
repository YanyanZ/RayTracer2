#ifndef TRACER_HPP
# define TRACER_HPP

# include <cmath>
# include <values.h>
# include <stdlib.h>
# include <fstream>

# include <object/Object.hpp>
# include <scene/Camera.hpp>
# include <light/Light.hpp>
# include <scene/Background.hpp>
# include <scene/Scene.hpp>

# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

# define maxVal 255

using namespace Tools;
using namespace Form;

namespace Engine
{
  class Tracer
  {
  private:
    Scene* s;
    double pheight, pwidth;
    double pasx, pasy;

  private:
    std::vector<double> aLight;
    std::vector<double> cBackground;

  private:
    double nbThrowRay;
    int width, height;
    unsigned char *map;

  public:
    Tracer(Scene * s);
    ~Tracer(void);

  public:
    void setPixel (int x, int y, std::vector<double> c);
    void getPixel (int x, int y, std::vector<double> c);

  public:
    void initRay(double x, double y, Ray *r);
    void throwRay(Ray *r, int deep, std::vector<double> coul);
    void throwRays(int i, int j, std::vector<double> coul);
    double evalHit(Ray* r, std::vector<double> hit,
		   Object** o);
    void evalDirectRadiance (Ray* r, Object* o,
			     std::vector<double> hit,
			     std::vector<double> normal,
			     std::vector<double> coul);
    void evalReflectRadiance(Ray* r, Object* o,
			     std::vector<double> hit,
			     std::vector<double> normal,
			     int deep,
			     std::vector<double> coul);
    void evalSendRadiance(Ray* r, Object* o,
			  std::vector<double> hit,
			  std::vector<double> normal,
			  int deep,
			  std::vector<double> coul);
    void evalAmbiantRadiance(Object* o,
			     std::vector<double> p,
			     std::vector<double> coul);

  public:
    void createScene(void);
    void saveScene(std::string output);
  };
}

#endif
