#ifndef __LECTEURSCENE__
#define      __LECTEURSCENE__

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "lecteurSym.h"

#include <perlin/PerlinNoise.hpp>
#include <texture/Checker.hpp>
#include <texture/Mapper.hpp>

#include <light/Ambiant.hpp>
#include <light/Point.hpp>
#include <light/Directional.hpp>

#include <tools/Transformer.hpp>

#include <scene/Scene.hpp>
#include <object/Sphere.h>
#include <object/Plan.hpp>
#include <object/Cylindre.hpp>
#include <object/Cone.hpp>
#include <object/Box.hpp>
#include <object/Triangle.hpp>
#include <object/Parallelogram.hpp>
#include <object/Tore.hpp>
#include <object/Cube.hpp>
//#include <object/Pyramid3.hpp>
//#include <object/Pyramid4.hpp>

using namespace Engine;
using namespace Lightning;
using namespace Generation;
using namespace Texture;

class lecteurScene
{

private:

 struct MODIFIER
  {
    double ambient;
    double diffuse;
    double specular;
    double transparency;
    double reflection;
    double shininess;
    double ior;
    double couleur[3];
    int typePigment;
    char texture[20];
    int typeNormale;
    checker *ccr;
    perlinNoise *pNoise;
    perlinNoise *pNormale;
    textureMapper *mapper;

  };

 /* les parametres pour la lecture de la scene*/
 lecteurSym ls;
 char nomFich[50];
 char ch[30];
 int code;

  void lireScene ();
  void lireBloc ();
  void lireCamera (double *fov,int *typeProjection,double * projectionS, double *position,
		   double *lookAt);
  void lireGlobalSetting (int *mtl, int *aa, double *aaT, double *softS, int *nbRO, int *width, int *height);
  void lireLightSource (double *position,double * direction, double *couleur, int *typeLum,
			double *c1, double *c2, double *c3);
  void lireBackground (double *couleur);
  void lireModifier (struct MODIFIER *m);
  void lireSphere (double *rayon, struct MODIFIER *m);
  void lirePlan (struct MODIFIER *m);
  void lireCylindre (double *rayon, double *longueur, struct MODIFIER *m);
  void lireCone (double *rayon, double *rayon2, double *longueur,
		 struct MODIFIER *m);
  void lireBox (double *cote, struct MODIFIER *m);
  void lireTriangle (double *p1, double *p2, double *p3, struct MODIFIER *m);
  void lireParallelogram (double *p1, double *p2, double *p3, struct MODIFIER *m);
  void lireTorus (double *minusR, double *majorR, struct MODIFIER *m);
  void lirePyramid (double base1[3], double base2[3], double base3[3],
		    double sommet[3], struct MODIFIER *m);

  void lireCubeTroue (struct MODIFIER *m);
  void lireTransform (struct MODIFIER *m);
  void lirePigment (struct MODIFIER *m);
  void lireTexture (struct MODIFIER *m);
  void lireChecker (struct MODIFIER *m);
  void lirePerlin (struct MODIFIER *m, int type);
  void lireColorMap (struct MODIFIER *m);
  void lireNormal (struct MODIFIER *m);
  void lireFinish (struct MODIFIER *m);
  void lireNombreFloat (double *n);
  void lireNombreInt (int *n);
  void lireTriplet (double *n1, double *n2, double *n3);
  void lireChaine (char *c);
  void afficherErreur (char *libelle);

  /* la scene a lire */
  scene *s;

  /* les parametres de la camera */
  camera *c;
  double fov;
  double lookAt[4];
  double posCam[4];
  int typeProjection;
  double projS;

  /* parametres background */
  double coulBg[3];

  /* parametres lumiere */
  lumiereDirectionnelle *ld;
  lumierePonctuelle * lp;
  lumiereAmbiante * la;
  double posLum[4];
  double dirLum[4];
  double coulLum[3];
  int typeLum;
  double c1, c2, c3;

  /* parametres global_setting */
  int maxTraceLevel;
  int antialiasing;
  double AAThreshold;
  int outputHeight;
  int outputWidth;
  double softShadow ;
  int nbRayonsOmbres;

  /* parametres pour les objets */
  struct MODIFIER m;
  double rayon, rayon2;
  double longueur;
  double cote;
  double p1[4], p2[4], p3[4], p4[4];
  double base1[3], base2[3], base3[3], base4[3];
  double sommet[3];

  void initParametres ();
  void setModifier (objet * o, struct MODIFIER m);

  /* parametre de transformation objet*/
  double scale[3];
  double rotate[3];
  double translate[3];

  /* parametre de transformation pigment*/
  double scalePm[3];
  double rotatePm[3];
  double translatePm[3];

  /* parametre de transformation normale*/
  double scaleN[3];
  double rotateN[3];
  double translateN[3];

  transformer * trans;


/* parametres pour le bruit de perlin */
  double alpha;
  double beta;
  int octave;
  double colorMap[100][3];
  double range[100];
  double intensite;
  enum { PIGMENT, NORMAL };

  /* parametres pour le pigment checker */
  double size;
  double couleur1[3], couleur2[3];

  /* parametres pour la texture */
  int freq;

  /* les objets */
  sphere *laSphere;
  plan *lePlan;
  cylindre *leCylindre;
  cone *leCone;
  box *laBox;
  triangle *leTriangle;
  tore *leTore;
  cubeTroue *leCubeTroue;
  parallelogram *leParallelogram;
  pyramid3 *laPyramid3;
  pyramid4 *laPyramid4;

public:
    lecteurScene (char nomFich[]);
  scene *getScene ();
};


#endif // __LECTEURSCENE__
