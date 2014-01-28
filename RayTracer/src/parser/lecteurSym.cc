
/***************************************************************************************/
/*						                                       */
/* Realise par : 	BONFORT THOMAS		                                       */
/*		        CHAIGNEAU DELPHINE	                                       */
/*			GALIZZI OLIVIER			                               */
/*			HEIGEAS LAURE		                                       */
/*                                                                                     */
/* Date :		20/05/2001	                                               */
/*                                                                                     */
/* Commentaires : permet de lire un fichier symboles par symgoles                      */
/*                                                                                     */
/***************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#include "lecteurSym.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

lecteurSym::lecteurSym (char nomFich[]):
lc (nomFich)
{
  symboleSuivant ();
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurSym::symboleSuivant ()
{

  char c = ' ';
  bool commentaires = false;

  while (c != '*' && (lc.peek () == ' ') || (lc.peek () == '\n')
	 || (lc.peek () == '\t') || (lc.peek () == '#' || commentaires))
    {
      if (lc.peek () == '#')
	commentaires = true;
      if (commentaires && lc.peek () == '\n')
	commentaires = false;
      lc.get (c);
    }
  if (c == '*')
    code = FIN;
  else
    {
      if (isdigit (lc.peek ()) || lc.peek () == '-')
	lireNombre ();
      else if (isalpha (lc.peek ()))
	lireMot ();
      else
	lireSpecial ();
    }

  /* if (c=='*')
     cout << "\t# fin" << endl;
     else
     cout << "\t# " << ch  << endl; */
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurSym::lireNombre ()
{

  int nbCar = 0;
  bool decimal = false;

  do
    {
      lc.get (ch[nbCar++]);
      if (ch[nbCar - 1] == '.')
	decimal = true;
    }
  while ((isdigit (lc.peek ()) || (lc.peek () == '.' && !decimal)));

  code = NOMBRE;

  ch[nbCar] = '\0';


}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurSym::lireMot ()
{

  int nbCar = 0;
  char c;

  do
    {
      lc.get (ch[nbCar++]);
      ch[nbCar - 1] = toupper (ch[nbCar - 1]);
    }
  while (lc.peek () != '\n' && lc.peek () != ' ' && lc.peek () != '\t'
	 && (lc.peek () == '_' || lc.peek () == '.' || isalpha (lc.peek ())
	     || isdigit (lc.peek ())));

  ch[nbCar] = '\0';

  if (!strcmp (ch, "CAMERA"))
    code = CAMERA;
  else if (!strcmp (ch, "BACKGROUND"))
    code = BACKGROUND;
  else if (!strcmp (ch, "LIGHT_SOURCE"))
    code = LIGHT_SOURCE;
  else if (!strcmp (ch, "GLOBAL_SETTING"))
    code = GLOBAL_SETTING;
  else if (!strcmp (ch, "SPHERE"))
    code = SPHERE;
  else if (!strcmp (ch, "CUBE_TROUE"))
    code = CUBE_TROUE;
  else if (!strcmp (ch, "PLAN"))
    code = PLAN;
  else if (!strcmp (ch, "CYLINDRE"))
    code = CYLINDRE;
  else if (!strcmp (ch, "CONE"))
    code = CONE;
  else if (!strcmp (ch, "BOX"))
    code = BOX;
  else if (!strcmp (ch, "TRIANGLE"))
    code = TRIANGLE;
  else if (!strcmp (ch, "PARALLELOGRAM"))
    code = PARALLELOGRAM;
  else if (!strcmp (ch, "TORUS"))
    code = TORUS;
  else if (!strcmp (ch, "PYRAMID3"))
    code = PYRAMID3;
  else if (!strcmp (ch, "PYRAMID4"))
    code = PYRAMID4;
  else if (!strcmp (ch, "LOCATION"))
    code = LOCATION;
  else if (!strcmp (ch, "DIRECTION"))
    code = DIRECTION;
  else if (!strcmp (ch, "LOOK_AT"))
    code = LOOK_AT;
  else if (!strcmp (ch, "FIELD_OF_VIEW"))
    code = FIELD_OF_VIEW;
  else if (!strcmp (ch, "PROJECTION_SIZE"))
    code = PROJECTION_SIZE;
  else if (!strcmp (ch, "COLOR"))
    code = COLOR;
  else if (!strcmp (ch, "ATTENUATION"))
    code = ATTENUATION;
  else if (!strcmp (ch, "TEXTURE"))
    code = TEXTURE;
  else if (!strcmp (ch, "MAX_TRACE_LEVEL"))
    code = MAX_TRACE_LEVEL;
  else if (!strcmp (ch, "OUTPUT_HEIGHT"))
    code = OUTPUT_HEIGHT;
  else if (!strcmp (ch, "OUTPUT_WIDTH"))
    code = OUTPUT_WIDTH;
  else if (!strcmp (ch, "ANTIALIASING"))
    code = ANTIALIASING;
  else if (!strcmp (ch, "AA_THRESHOLD"))
    code = AA_THRESHOLD;
  else if (!strcmp (ch, "ROTATE"))
    code = ROTATE;
  else if (!strcmp (ch, "TRANSLATE"))
    code = TRANSLATE;
  else if (!strcmp (ch, "SCALE"))
    code = SCALE;
  else if (!strcmp (ch, "FINISH"))
    code = FINISH;
  else if (!strcmp (ch, "AMBIENT"))
    code = AMBIENT;
  else if (!strcmp (ch, "DIFFUSE"))
    code = DIFFUSE;
  else if (!strcmp (ch, "SPECULAR"))
    code = SPECULAR;
  else if (!strcmp (ch, "SHININESS"))
    code = SHININESS;
  else if (!strcmp (ch, "TRANSPARENCY"))
    code = TRANSPARENCY;
  else if (!strcmp (ch, "IOR"))
    code = IOR;
  else if (!strcmp (ch, "REFLECTION"))
    code = REFLECTION;
  else if (!strcmp (ch, "TRANSFORM"))
    code = TRANSFORM;
  else if (!strcmp (ch, "PIGMENT"))
    code = PIGMENT;
  else if (!strcmp (ch, "NORMAL"))
    code = NORMAL;
  else if (!strcmp (ch, "AMBIENT"))
    code = AMBIENT;
  else if (!strcmp (ch, "DIRECTIONNAL"))
    code = DIRECTIONNAL;
  else if (!strcmp (ch, "POINT_SOURCE"))
    code = POINT_SOURCE;
  else if (!strcmp (ch, "CHECKER"))
    code = CHECKER;
  else if (!strcmp (ch, "PERLIN"))
    code = PERLIN;
  else if (!strcmp (ch, "MARBLE"))
    code = MARBLE;
  else if (!strcmp (ch, "WOOD"))
    code = WOOD;
  else if (!strcmp (ch, "COLOR_MAP"))
    code = COLOR_MAP;
  else if (!strcmp (ch, "ATTENUATION"))
    code = ATTENUATION;
  else if (!strcmp (ch, "SOFT_SHADOW"))
    code = SOFT_SHADOW;
  else if (!strcmp (ch, "SHADOW_RAY"))
    code = SHADOW_RAY;
  else if (!strcmp (ch, "PERSPECTIVE"))
    code = PERSPECTIVE;
  else if (!strcmp (ch, "ORTHOGRAPHIC"))
    code = ORTHOGRAPHIC;
  else
    code = CHAINE;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurSym::lireSpecial ()
{

  int nbCar = 0;

  switch (lc.peek ())
    {
    case '{':
      lc.get (ch[nbCar++]);
      code = ACCOLADE_OUVRANTE;
      break;
    case '}':
      lc.get (ch[nbCar++]);
      code = ACCOLADE_FERMANTE;
      break;
    case '[':
      lc.get (ch[nbCar++]);
      code = CROCHET_OUVRANT;
      break;
    case ']':
      lc.get (ch[nbCar++]);
      code = CROCHET_FERMANT;
      break;
    case ',':
      lc.get (ch[nbCar++]);
      code = VIRGULE;
      break;
    case '<':
      lc.get (ch[nbCar++]);
      code = CHEVRON_OUVRANT;
      break;
    case '>':
      lc.get (ch[nbCar++]);
      code = CHEVRON_FERMANT;
      break;
    default:
      code = INDEFINI;
      break;
    }

  ch[nbCar] = '\0';

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

bool
lecteurSym::sauterSymbole (int valCode)
{

  if (code == valCode)
    {
      symboleSuivant ();
      return true;
    }
  else
    return false;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int
lecteurSym::codeSymboleCourant ()
{
  return code;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

char *
lecteurSym::chaineSymboleCourant ()
{
  return ch;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int
lecteurSym::getNumeroLigneCourante ()
{

  return lc.getNumeroLigneCourante ();

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

char *
lecteurSym::getLigneCourante ()
{

  return lc.getLigneCourante ();

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
