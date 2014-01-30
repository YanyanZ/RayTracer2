# include <parser/SceneParser.hpp>
# include <scene/Tracer.hpp>
# include <vector>

#include <light/Ambiant.hpp>
#include <light/Point.hpp>

#include <tools/Transformer.hpp>

#include <scene/Scene.hpp>
#include <object/Sphere.hpp>
#include <object/Plan.hpp>
#include <object/Triangle.hpp>

using namespace Engine;
using namespace Tools;
using namespace Lightning;
using namespace Form;

int main (int argc, char *argv[])
{
  if (argc == 3)
  {
    /* lecture et recuperation de la description de la scene */
    SceneParser sp(argv[1]);
    sp.parse();

    Scene* s = sp.getScene();

    int c1 = 0;
    int c2 = 0;
    int c3 = 0;
    double color[3] = {1, 1, 1};

    double l1pos[3] = {3, -5, 0};
    double l1c[4] = {1.0, 1.0, 1.0};

    double l2pos[3] = {2, 1, 0};
    double l2c[4] = {1.0, 1.0, 1.0};

    double l3ac[4] = {1, 1, 1};

    double sm1[4] = {0, 0, 0, 0};
    double sm2[4] = {1, 0, 1, 0};
    double sm3[4] = {0, 2, 0, 0};

    Sphere* o = new Sphere(5);
    Triangle* tr = new Triangle(sm1, sm2, sm3);
    // Les autres paramettres sont identique au cercle et plan. La seul chose qui change
    // ce sont les constructeurs
    o->setRhoA(0);
    o->setRhoD(0);
    o->setRhoS(1);
    o->setRhoT(0.5);
    o->setColor(color);
    o->setN(1.0);
    o->setShininess(50);
    int typePigment = Object::COLOR;

    double translate[3] = {2, 3, 10};
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

    Plan* p = new Plan();
    p->setRhoA(0.2);
    p->setRhoD(0.4);
    p->setRhoS(0.8);
    p->setRhoT(0.0);
    p->setColor(color);
    p->setN(1.0);
    p->setShininess(40);

    double ptranslate[3] = {-2, 0, 0};
    double protate[3] = {0, 0, 0};
    double pscale[4] = {1.0, 1.0, 1.0};
    double pcolor[3] = {0.1, 0.1, 0.5};
    p->setColor(pcolor);

    Transformer* trans2 = new Transformer();
    trans2->setTranslation(ptranslate);
    trans2->setRotation(protate);
    trans2->setScale(pscale);
    p->setTransformer(trans2);
    p->setTypePigment(typePigment);
    p->setTypeNormal(typeNormale);

    Ambiant* la = new Ambiant(l3ac);
    s->addAmbiant(la);

    Point* lp1 = new Point(l1pos, l1c);
    lp1->setDimming(c1, c2, c3);
    s->addPoint(lp1);

    Point* lp2 = new Point(l2pos, l2c);
    lp2->setDimming(c1, c2, c3);
    s->addPoint(lp2);

    s->addObject(o);
    s->addObject(p);

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
