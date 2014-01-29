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
    double aLight[3];
    double cBackground[3];

  private:
    double nbThrowRay;
    int width, height;
    unsigned char *map;

  public:
    Tracer(Scene* s);
    ~Tracer(void);

  public:
    void setPixel (int x, int y, double c[3]);
    void getPixel (int x, int y, double c[3]);

  public:
    void initRay(double x, double y, Ray *r);
    void throwRay(Ray *r, int deep, double coul[3]);
    void throwRays(int i, int j, double coul[3]);
    double evalHit(Ray* r, double hit[4],
		   Object** o);
    void evalDirectRadiance (Ray* r, Object* o,
			     double hit[4],
			     double normal[4],
			     double coul[3]);
    void evalReflectRadiance(Ray* r, Object* o,
			     double hit[4],
			     double normal[4],
			     int deep,
			     double coul[3]);
    void evalSendRadiance(Ray* r, Object* o,
			  double hit[4],
			  double normal[4],
			  int deep,
			  double coul[3]);
    void evalAmbiantRadiance(Object* o,
			     double p[3],
			     double coul[3]);

  public:
    void createScene(void);
    void saveScene(std::string output);
  };
}

#endif
