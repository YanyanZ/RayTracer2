#ifndef __LECTEURSYM__
#define      __LECTEURSYM__

#include <ctype.h>
#include <string.h>
#include <stdlib.h>

#include "lecteurCar.h"

class lecteurSym
{

private:
  lecteurCar lc;
  char ch[30];
  int code;
  void lireNombre ();
  void lireSpecial ();
  void lireMot ();

public:
    lecteurSym (char nomFich[]);
  void symboleSuivant ();
  bool sauterSymbole (int valCode);
  int codeSymboleCourant ();
  char *chaineSymboleCourant ();
  int getNumeroLigneCourante ();
  char *getLigneCourante ();

  enum
  {
    INDEFINI,
    FIN,
    ACCOLADE_OUVRANTE,
    ACCOLADE_FERMANTE,
    CROCHET_OUVRANT,
    CROCHET_FERMANT,
    CHEVRON_OUVRANT,
    CHEVRON_FERMANT,
    VIRGULE,
    TRIPLET,
    NOMBRE,
    CHAINE,
    CAMERA,
    BACKGROUND,
    LIGHT_SOURCE,
    GLOBAL_SETTING,
    SPHERE,
    CUBE_TROUE,
    PLAN,
    CYLINDRE,
    CONE,
    BOX,
    TRIANGLE,
    PARALLELOGRAM,
    TORUS,
    PYRAMID3,
    PYRAMID4,
    LOCATION,
    DIRECTION,
    LOOK_AT,
    FIELD_OF_VIEW,
    PROJECTION_SIZE,
    COLOR,
    ATTENUATION,
    TEXTURE,
    MAX_TRACE_LEVEL,
    OUTPUT_HEIGHT,
    OUTPUT_WIDTH,
    ANTIALIASING,
    AA_THRESHOLD,
    ROTATE,
    TRANSLATE,
    SCALE,
    FINISH,
    AMBIENT,
    DIFFUSE,
    SPECULAR,
    SHININESS,
    TRANSPARENCY,
    IOR,
    REFLECTION,
    TRANSFORM,
    PIGMENT,
    NORMAL,
    DIRECTIONNAL,
    POINT_SOURCE,
    CHECKER,
    PERLIN,
    WOOD,
    MARBLE,
    COLOR_MAP,
    SOFT_SHADOW,
    SHADOW_RAY,
    PERSPECTIVE,
    ORTHOGRAPHIC

  };


};


#endif // __LECTEURSYM__
