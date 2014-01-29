//# include <parser/SceneParser.hpp>
# include <vector>

# include <scene/Tracer.hpp>

#include <light/Ambiant.hpp>
#include <light/Point.hpp>

#include <tools/Transformer.hpp>

#include <scene/Scene.hpp>
#include <object/Sphere.hpp>

using namespace Engine;
using namespace Tools;
using namespace Lightning;
using namespace Form;

int main (int argc, char *argv[])
{
  if (argc == 3)
  {
    Scene* s = new Scene();

    double max_trace_level = 3.0;
    int owidth = 1024;
    int oheight = 768;
    int anti = 1;
    double threshold = 0.3;
    int shadow = -1;
    int nbrays = 1;

    double cBG[3] = {0, 0, 0};
    double color[3] = {1, 0, 0};

    int c1 = 1;
    int c2 = 0;
    int c3 = 0;

    double l1pos[3] = {3, -5, 0};
    double l1c[4] = {1.0, 1.0, 1.0};

    double l2pos[3] = {2, 1, 0};
    double l2c[4] = {1.0, 1.0, 1.0};

    double l3ac[4] = {0.5, 0.5, 0.5};

    double campos[4] = {0.2, 0.0, -0.1};
    double lookat[3] = {0, 0, 1};
    double fov = 130;

    Sphere* o = new Sphere(2.5);
    o->setRhoA(0.3);
    o->setRhoD(0.3);
    o->setRhoS(0.9);
    o->setRhoT(0.5);
    o->setColor(color);
    o->setN(1.0);
    o->setShininess(50);
    int typePigment = Object::COLOR;

    double translate[3] = {-1, 0, 4};
    double rotate[3] = {0, 0, 0};
    double scale[4] = {1.0, 1.0, 1.0};

    int typeNormale = Object::NO;

    Transformer* trans = new Transformer();
    trans->setTranslation(translate);
    trans->setRotation(rotate);
    trans->setScale(scale);
    o->setTransformer(trans);
    o->setTypePigment(typePigment);
    o->setTypeNormal(typeNormale);

    s->setBackground(cBG);
    s->setGlobalSetting(max_trace_level, anti, threshold, shadow,
			nbrays, oheight, owidth);

    Camera* c = new Camera(campos, lookat);
    c->setTProjection(Camera::PERSPECTIVE);
    c->setSProjection(10);
    c->setFov(fov);
    s->changeCamera (c);

    Ambiant* la = new Ambiant(l3ac);
    s->addAmbiant (la);

    Point* lp1 = new Point(l1pos, l1c);
    lp1->setDimming(c1, c2, c3);
    s->addPoint(lp1);

    Point* lp2 = new Point(l2pos, l2c);
    lp2->setDimming(c1, c2, c3);
    s->addPoint(lp2);

    s->addObject(o);

    Tracer* t = new Tracer(s);

    /* lancement du rendu de la scene */
    t->createScene ();

    /* sauvegarde de la scene dans le fichier de sortie */
    t->saveScene (argv[2]);

    return 1;
  }
  else
  {
    std::cerr << "[RAYTRACER][ERROR] - Bad usage - ./exe sceneDescriptor.xml outfile";
    std::cerr << std::endl;
    return -1;
  }
}
