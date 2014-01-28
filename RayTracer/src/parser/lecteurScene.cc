#include "lecteurScene.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

lecteurScene::lecteurScene (char nomFich[]):
ls (nomFich)
{

  s = new scene ();
  strcpy (this->nomFich, nomFich);
  initParametres ();
  lireScene ();

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

scene *
lecteurScene::getScene ()
{
  return s;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::initParametres ()
{

  /* initialisation parametres cameras */
  fov = 60.0;
  typeProjection = camera::PERSPECTIVE;
  projS = 10;
  lookAt[0] = 0.0;
  lookAt[1] = 0.0;
  lookAt[2] = 0.0;
  lookAt[3] = 1.0;
  posCam[0] = 0.0;
  posCam[1] = 0.0;
  posCam[2] = 0.0;
  posCam[3] = 1.0;

  /* initialisation parametres background */
  coulBg[0] = 0.5;
  coulBg[1] = 0.5;
  coulBg[2] = 0.5;

  /* initialisation parametres lumieres */
  posLum[0] = 0.0;
  posLum[1] = 0.0;
  posLum[2] = 0.0;
  posLum[3] = 1.0;
  dirLum[0] = 0.0;
  dirLum[1] = 0.0;
  dirLum[2] = 1.0;
  dirLum[3] = 0.0;
  coulLum[0] = 1.0;
  coulLum[1] = 1.0;
  coulLum[2] = 1.0;
  typeLum = lecteurSym::POINT_SOURCE;
  c1 = 1;
  c2 = 0;
  c3 = 0;

  /* initialisation parametres global_setting */
  maxTraceLevel = 4;
  antialiasing = 1;
  AAThreshold = 0.3;
  outputHeight = 480;
  outputWidth = 640;
  softShadow =-1.0;
  nbRayonsOmbres=1;

  /* initialisation coordonnees homogenes des points du triangles */
  p1[3] = 1.0;
  p2[4] = 1.0;
  p3[3] = 1.0;

  /* initialisation modifier */
  m.ambient = 0.4;
  m.diffuse = 0.7;
  m.specular = 0.8;
  m.transparency = 0.0;
  m.reflection = 0.0;
  m.shininess = 40;
  m.ior = 1.0;

  /* initialiation pigment*/
  m.couleur[0] = 1.0;
  m.couleur[1] = 1.0;
  m.couleur[2] = 1.0;
  m.typePigment = objet::COULEUR;
  m.ccr = new checker ();
  m.pNoise = new perlinNoise ();
  m.pNormale = new perlinNoise ();
  m.mapper = new textureMapper ();
  
  translate[0] = 0.0;
  translate[1] = 0.0;
  translate[2] = 0.0;
  rotate[0] = 0.0;
  rotate[1] = 0.0;
  rotate[2] = 0.0;
  scale[0] = 1.0;
  scale[1] = 1.0;
  scale[2] = 1.0;

  translatePm[0] = 0.0;
  translatePm[1] = 0.0;
  translatePm[2] = 0.0;
  rotatePm[0] = 0.0;
  rotatePm[1] = 0.0;
  rotatePm[2] = 0.0;
  scalePm[0] = 1.0;
  scalePm[1] = 1.0;
  scalePm[2] = 1.0;
  
  translateN[0] = 0.0;
  translateN[1] = 0.0;
  translateN[2] = 0.0;
  rotateN[0] = 0.0;
  rotateN[1] = 0.0;
  rotateN[2] = 0.0;
  scaleN[0] = 1.0;
  scaleN[1] = 1.0;
  scaleN[2] = 1.0;

  trans = new transformer();

  m.typeNormale = objet::NO;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::setModifier (objet * o, struct MODIFIER m)
{

  o->setRhoA (m.ambient);
  o->setRhoD (m.diffuse);
  o->setRhoS (m.specular);
  o->setRhoR (m.reflection);
  o->setRhoT (m.transparency);
  o->setN (m.ior);
  o->setShininess (m.shininess);

  trans = new transformer();
  trans->setTranslation(translate);
  trans->setRotation(rotate);
  trans->setEchelle(scale);

  o->setTransformer (trans);

  o->setTypePigment (m.typePigment);

  trans = new transformer();
  trans->setTranslation(translatePm);
  trans->setRotation(rotatePm);
  trans->setEchelle(scalePm);

  switch (m.typePigment)
    {
    case objet::COULEUR:
      o->setCouleur (m.couleur);
      break;
    case objet::CHECKER:
      m.ccr->setTransformer(trans);
      o->setChecker (m.ccr);
      break;
    case objet::PERLIN:
      m.pNoise->setTransformer(trans);
      o->setPerlin (m.pNoise);       
      break;    
    case objet::TEXTURE_MAPPING:
      m.mapper->setTransformer(trans);
      o->setMapper (m.mapper);
      break;
    default:
      o->setCouleur (m.couleur);
      break;
    }

  o->setTypeNormale (m.typeNormale);

  if (m.typeNormale==objet::PERLIN) {
    trans = new transformer();
    trans->setTranslation(translateN);
    trans->setRotation(rotateN);   
    trans->setEchelle(scaleN);
    m.pNormale->setTransformer (trans);      
    o->setPerlinNormale (m.pNormale);
  }

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::afficherErreur (char *libelle)
{
  cout << endl;
  cout << "raytracer : *** Erreur [" << nomFich << "] :" << endl;
  cout << " \tligne " << ls.
    getNumeroLigneCourante () << " : " << "[ " << ls.getLigneCourante () <<
    " ]" << endl;
  cout << "\t\t  " << libelle << endl << endl;
  exit (0);
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireScene ()
{

  cout << "\tDebut lecture du fichier \"" << nomFich << "\" " << endl;

  while (ls.codeSymboleCourant () != lecteurSym::FIN)
    {
      initParametres ();
      lireBloc ();
      ls.symboleSuivant ();
    }

  cout << "\tFin lecture du fichier \"" << nomFich << "\" ";
  cout << "\t [   OK   ]" << endl << endl;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireBloc ()
{

  switch (ls.codeSymboleCourant ())
    {
    case lecteurSym::CAMERA:
      lireCamera (&fov,&typeProjection,&projS, posCam, lookAt);
      c = new camera (posCam, lookAt);
      c->setTypeProjection(typeProjection);
      c->setProjectionSize(projS);
      if (typeProjection==camera::PERSPECTIVE) {
	c->setFov(fov);
      }
      s->changerCamera (c);
      cout << "\t\tAjout camera \t\t\t [   OK   ]" << endl;
      break;
    case lecteurSym::BACKGROUND:
      lireBackground (coulBg);
      s->setBackground (coulBg);
      cout << "\t\tAjout background \t\t [   OK   ]" << endl;
      break;
    case lecteurSym::LIGHT_SOURCE:
      lireLightSource (posLum,dirLum, coulLum, &typeLum, &c1, &c2, &c3);
      if (c1 == 0 && c2 == 0 && c3 == 0 || c1 < 0 || c2 < 0 || c3 < 0)
	afficherErreur("les coefficients d'attenuation de la lumiere ne peuvent pas etre negatif ou tous nul ");
      switch (typeLum){
      case lecteurSym::POINT_SOURCE :
	lp = new lumierePonctuelle (posLum, coulLum);
	lp->setAttenuation (c1, c2, c3);
	s->ajouterLumierePonctuelle (lp);
	break;
      case lecteurSym::DIRECTIONNAL :
	ld = new lumiereDirectionnelle (dirLum, coulLum);
	s->ajouterLumiereDirectionnelle (ld);
	break;
      case lecteurSym::AMBIENT :
	la = new lumiereAmbiante(coulLum);
	s->ajouterLumiereAmbiante (la);
	break;
      default : break;
      }
      cout << "\t\tAjout light_source \t\t [   OK   ]" << endl;
      break;
    case lecteurSym::GLOBAL_SETTING:
      lireGlobalSetting (&maxTraceLevel, &antialiasing, &AAThreshold, &softShadow, &nbRayonsOmbres,&outputWidth, &outputHeight);
      s->setGlobalSetting (maxTraceLevel, antialiasing, AAThreshold, softShadow, nbRayonsOmbres, outputHeight, outputWidth);
      cout << "\t\tAjout global_setting \t\t [   OK   ]" << endl;
      break;
    case lecteurSym::SPHERE:
      lireSphere (&rayon, &m);
      laSphere = new sphere (rayon);
      setModifier (laSphere, m);
      if (m.typePigment == objet::TEXTURE_MAPPING){
	  m.mapper->setTextureSphere (rayon);
	  //laSphere->setMapper (m.mapper);
	}
      s->ajouterObjet (laSphere);
      cout << "\t\tAjout sphere \t\t\t [   OK   ]" << endl;
      break;
    case lecteurSym::PLAN:
      lirePlan (&m);
      lePlan = new plan ();
      setModifier (lePlan, m);
      if (m.typePigment == objet::TEXTURE_MAPPING){
	  m.mapper->setTexturePlan ();
	  //lePlan->setMapper (m.mapper);
	}
      s->ajouterObjet (lePlan);
      cout << "\t\tAjout plan \t\t\t [   OK   ]" << endl;
      break;
    case lecteurSym::CYLINDRE:
      lireCylindre (&rayon, &longueur, &m);
      leCylindre = new cylindre (rayon, longueur);
      setModifier (leCylindre, m);
      s->ajouterObjet (leCylindre);
      cout << "\t\tAjout cylindre \t\t\t [   OK   ]" << endl;
      break;
    case lecteurSym::CONE:
      lireCone (&rayon, &rayon2, &longueur, &m);
      leCone = new cone (rayon2, rayon, longueur);
      setModifier (leCone, m);
      s->ajouterObjet (leCone);
      cout << "\t\tAjout cone \t\t\t [   OK   ]" << endl;

      break;
    case lecteurSym::BOX:
      lireBox (&cote, &m);
      laBox = new box (cote);
      setModifier (laBox, m);
      s->ajouterObjet (laBox);
      cout << "\t\tAjout box \t\t\t [   OK   ]" << endl;
      break;
    case lecteurSym::TRIANGLE:
      lireTriangle (p1, p2, p3, &m);
      leTriangle = new triangle (p1, p2, p3);
      setModifier (leTriangle, m);
      s->ajouterObjet (leTriangle);
      cout << "\t\tAjout triangle \t\t\t [   OK   ]" << endl;
      break;
    case lecteurSym::PARALLELOGRAM:
      lireParallelogram (p1, p2, p3, &m);
      leParallelogram = new parallelogram (p1, p2, p3);
      setModifier (leParallelogram, m);
      s->ajouterObjet (leParallelogram);
      cout << "\t\tAjout parallelogram \t\t [   OK   ]" << endl;
      break;
    case lecteurSym::TORUS:
      lireTorus (&rayon, &rayon2, &m);
      leTore = new tore (rayon, rayon2);
      setModifier (leTore, m);
      s->ajouterObjet (leTore);
      cout << "\t\tAjout tore \t\t\t [   OK   ]" << endl;
      break;
    case lecteurSym::CUBE_TROUE:
      lireCubeTroue (&m);
      leCubeTroue = new cubeTroue ();
      setModifier (leCubeTroue, m);
      s->ajouterObjet (leCubeTroue);
      cout << "\t\tAjout cube_troue \t\t [   OK   ]" << endl;
      break;
    case lecteurSym::PYRAMID3:
      ls.sauterSymbole (lecteurSym::PYRAMID3);
      lirePyramid (base1, base2, base3, sommet, &m);
      laPyramid3 = new pyramid3 (base1, base2, base3, sommet);
      setModifier (laPyramid3, m);
      s->ajouterObjet (laPyramid3);
      cout << "\t\tAjout pyramid3 \t\t\t [   OK   ]" << endl;
      break;
    case lecteurSym::PYRAMID4:
      ls.sauterSymbole (lecteurSym::PYRAMID4);
      lirePyramid (base1, base2, base3, sommet, &m);
      laPyramid4 = new pyramid4 (base1, base2, base3, sommet);
      setModifier (laPyramid4, m);
      s->ajouterObjet (laPyramid4);
      cout << "\t\tAjout pyramid4 \t\t\t [   OK   ]" << endl;
      break;
    default:
      afficherErreur ("bloc de type inconnu");
    }

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireCamera (double *fov,int *typeProjection,double * projectionS, double *position,
		   double *lookAt)
{

  ls.sauterSymbole (lecteurSym::CAMERA);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      while (ls.codeSymboleCourant () != lecteurSym::FIN
	     && ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
	{

	  switch (ls.codeSymboleCourant ())
	    {
	    case lecteurSym::LOCATION:
	      ls.sauterSymbole (lecteurSym::LOCATION);
	      lireTriplet (&position[0], &position[1], &position[2]);
	      break;
	    case lecteurSym::LOOK_AT:
	      ls.sauterSymbole (lecteurSym::LOOK_AT);
	      lireTriplet (&lookAt[0], &lookAt[1], &lookAt[2]);
	      break;
	    case lecteurSym::FIELD_OF_VIEW:
	      ls.sauterSymbole (lecteurSym::FIELD_OF_VIEW);
	      lireNombreFloat (fov);
	      break;
	    case lecteurSym::PROJECTION_SIZE:
	      ls.sauterSymbole (lecteurSym::PROJECTION_SIZE);
	      lireNombreFloat (projectionS);
	      break;
	    case lecteurSym::PERSPECTIVE:
	      ls.sauterSymbole (lecteurSym::PERSPECTIVE);
	      *typeProjection = camera::PERSPECTIVE;
	      break;
	    case lecteurSym::ORTHOGRAPHIC:
	      ls.sauterSymbole (lecteurSym::ORTHOGRAPHIC);
	      *typeProjection = camera::ORTHOGRAPHIC;
	      break;
	    default:
	      afficherErreur ("parametre camera inconnu ");
	    }
	}
      if (ls.codeSymboleCourant () == lecteurSym::FIN)
	afficherErreur ("il manque une accolade fermante ");
    }
  else
    afficherErreur ("il manque une accolade ouvrante ");

  if (*fov < 0)
    *fov = 60.0;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireBackground (double *couleur)
{

  ls.sauterSymbole (lecteurSym::BACKGROUND);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      while (ls.codeSymboleCourant () != lecteurSym::FIN
	     && ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
	{

	  switch (ls.codeSymboleCourant ())
	    {
	    case lecteurSym::COLOR:
	      ls.sauterSymbole (lecteurSym::COLOR);
	      lireTriplet (&couleur[0], &couleur[1], &couleur[2]);
	      break;
	    default:
	      afficherErreur ("parametre background inconnu ");
	    }
	}
      if (ls.codeSymboleCourant () == lecteurSym::FIN)
	afficherErreur ("il manque une accolade fermante ");

    }

  else
    afficherErreur ("il manque une accolade ouvrante ");

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireLightSource (double *position, double *direction, double *couleur,
			       int *typeLum, double *c1, double *c2,
			       double *c3)
{


  ls.sauterSymbole (lecteurSym::LIGHT_SOURCE);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {
      while (ls.codeSymboleCourant () != lecteurSym::FIN
	     && ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
	{

	  switch (ls.codeSymboleCourant ())
	    {
	    case lecteurSym::LOCATION:
	      if (*typeLum!=lecteurSym::POINT_SOURCE) {
		afficherErreur ("parametre LOCATION invalide pour toute source lumineuse non ponctuelle");	
	      }else {
		ls.sauterSymbole (lecteurSym::LOCATION);
		lireTriplet (&position[0], &position[1], &position[2]);
	      }
	      break;
	    case lecteurSym::DIRECTION:
	      if (*typeLum!=lecteurSym::DIRECTIONNAL) {
		afficherErreur ("parametre DIRECTION invalide pour toute source lumineuse non directionnelle");	
	      }else {
		ls.sauterSymbole (lecteurSym::DIRECTION);
		lireTriplet (&direction[0], &direction[1], &direction[2]);
	      }
	      break;
	    case lecteurSym::COLOR:
	      ls.sauterSymbole (lecteurSym::COLOR);
	      lireTriplet (&couleur[0], &couleur[1], &couleur[2]);
	      break;
	    case lecteurSym::POINT_SOURCE:
	      ls.sauterSymbole (lecteurSym::POINT_SOURCE);
	      *typeLum = lecteurSym::POINT_SOURCE;
	      break;
	    case lecteurSym::AMBIENT:
	      ls.sauterSymbole (lecteurSym::AMBIENT);
	      *typeLum = lecteurSym::AMBIENT;
	      break;
	    case lecteurSym::DIRECTIONNAL:
	      ls.sauterSymbole (lecteurSym::DIRECTIONNAL);
	      *typeLum = lecteurSym::DIRECTIONNAL;
	      break;
	    case lecteurSym::ATTENUATION:
	      ls.sauterSymbole (lecteurSym::ATTENUATION);
	      if (*typeLum!=lecteurSym::DIRECTIONNAL) {
		afficherErreur ("parametre ATTENUATION invalide pour toute source lumineuse non ponctuelle");	
	      }else 
		lireTriplet (c1, c2, c3);
	      break;
	    default:
	      afficherErreur ("parametre light_source inconnu ");
	    }
	}
      if (ls.codeSymboleCourant () == lecteurSym::FIN)
	afficherErreur ("il manque une accolade fermante ");

    }
  else
    afficherErreur ("il manque une accolade ouvrante");
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireGlobalSetting (int *mtl, int *aa, double *aaT, double *softS, int *nbRO, int *width, int *height)
{

  ls.sauterSymbole (lecteurSym::GLOBAL_SETTING);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      while (ls.codeSymboleCourant () != lecteurSym::FIN
	     && ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
	{

	  switch (ls.codeSymboleCourant ())
	    {
	    case lecteurSym::MAX_TRACE_LEVEL:
	      ls.sauterSymbole (lecteurSym::MAX_TRACE_LEVEL);
	      lireNombreInt (mtl);
	      break;
	    case lecteurSym::ANTIALIASING:
	      ls.sauterSymbole (lecteurSym::ANTIALIASING);
	      lireNombreInt (aa);
	      break;
	    case lecteurSym::AA_THRESHOLD:
	      ls.sauterSymbole (lecteurSym::AA_THRESHOLD);
	      lireNombreFloat (aaT);
	      break;
	    case lecteurSym::SOFT_SHADOW:
	      ls.sauterSymbole (lecteurSym::SOFT_SHADOW);
	      lireNombreFloat (softS);
	      break;
	    case lecteurSym::SHADOW_RAY:
	      ls.sauterSymbole (lecteurSym::SHADOW_RAY);
	      lireNombreInt (nbRO);
	      break;
	    case lecteurSym::OUTPUT_HEIGHT:
	      ls.sauterSymbole (lecteurSym::OUTPUT_HEIGHT);
	      lireNombreInt (height);
	      break;
	    case lecteurSym::OUTPUT_WIDTH:
	      ls.sauterSymbole (lecteurSym::OUTPUT_WIDTH);
	      lireNombreInt (width);
	      break;
	    default:
	      afficherErreur ("parametre global_setting inconnu ");
	    }
	}
      if (ls.codeSymboleCourant () == lecteurSym::FIN)
	afficherErreur ("il manque une accolade fermante ");
    }
  else
    afficherErreur ("il manque une accolade ouvrante ");

  if (*aa < 1)
    *aa = 1;
  if (*aa > 4)
    *aa = 4;
  if (*width < 0)
    *width = 640;
  if (*height < 0)
    *height = 480;
  if (*mtl < 0)
    *mtl = 0;
  if (*mtl > 10)
    *mtl = 10;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireSphere (double *rayon, struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::SPHERE);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {
      lireNombreFloat (rayon);
      lireModifier (m);
    }
  else
    afficherErreur ("il manque une accolade ouvrante");

  if (*rayon < 0)
    *rayon = 1.0;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lirePlan (struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::PLAN);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {
      lireModifier (m);
    }
  else
    afficherErreur ("il manque une accolade ouvrante");
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireCylindre (double *rayon, double *longueur,
			    struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::CYLINDRE);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      lireNombreFloat (rayon);
      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule");
      lireNombreFloat (longueur);
      lireModifier (m);
    }
  else
    afficherErreur ("il manque une accolade ouvrante");

  if (*rayon < 0)
    *rayon = 1.0;
  if (*longueur < 0)
    *longueur = 1.0;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireCone (double *rayon, double *rayon2, double *longueur,
			struct MODIFIER *m)
{
  {
    ls.sauterSymbole (lecteurSym::CONE);

    if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
      {
	lireNombreFloat (rayon);
	if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	  afficherErreur ("il manque une virgule");
	lireNombreFloat (rayon2);
	if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	  afficherErreur ("il manque une virgule");
	lireNombreFloat (longueur);
	lireModifier (m);
      }
    else
      afficherErreur ("il manque une accolade ouvrante");

    if (*rayon < 0)
      *rayon = 1.0;
    if (*rayon2 < 0)
      *rayon2 = 1.0;
    if (*longueur < 0)
      *longueur = 1.0;
  }


}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireBox (double *cote, struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::BOX);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      lireNombreFloat (cote);
      lireModifier (m);
    }
  else
    afficherErreur ("il manque une accolade ouvrante");

  if (*cote < 0)
    *cote = 1.0;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireTriangle (double *p1, double *p2, double *p3,
			    struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::TRIANGLE);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      lireTriplet (&p1[0], &p1[1], &p1[2]);
      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule apres le triplet ");
      lireTriplet (&p2[0], &p2[1], &p2[2]);
      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule apres le triplet ");
      lireTriplet (&p3[0], &p3[1], &p3[2]);
      lireModifier (m);
    }
  else
    afficherErreur ("il manque une accolade ouvrante");
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireParallelogram (double *p1, double *p2, double *p3,
			     struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::PARALLELOGRAM);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      lireTriplet (&p1[0], &p1[1], &p1[2]);
      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule apres le triplet ");
      lireTriplet (&p2[0], &p2[1], &p2[2]);
      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule apres le triplet ");
      lireTriplet (&p3[0], &p3[1], &p3[2]);
      lireModifier (m);
    }
  else
    afficherErreur ("il manque une accolade ouvrante");
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireTorus (double *minusR, double *majorR, struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::TORUS);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      lireNombreFloat (minusR);
      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule apres le triplet ");
      lireNombreFloat (majorR);
      lireModifier (m);
    }
  else
    afficherErreur ("il manque une accolade ouvrante");

  if (*minusR >= *majorR)
    afficherErreur
      ("le petit rayon du tore doit etre inferieur au grand rayon");

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireCubeTroue (struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::CUBE_TROUE);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {
      lireModifier (m);
    }
  else
    afficherErreur ("il manque une accolade ouvrante");
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lirePyramid (double base1[3], double base2[3], double base3[3],
			   double sommet[3], struct MODIFIER *m)
{


  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      lireTriplet (&base1[0], &base1[1], &base1[2]);
      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule apres le triplet ");
      lireTriplet (&base2[0], &base2[1], &base2[2]);
      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule apres le triplet ");
      lireTriplet (&base3[0], &base3[1], &base3[2]);
      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule apres le triplet ");
      lireTriplet (&sommet[0], &sommet[1], &sommet[2]);
      lireModifier (m);
    }
  else
    afficherErreur ("il manque une accolade ouvrante");

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireModifier (struct MODIFIER *m)
{

  while (ls.codeSymboleCourant () != lecteurSym::FIN
	 && ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
    {

      switch (ls.codeSymboleCourant ())
	{
	case lecteurSym::TRANSFORM:
	  lireTransform (m);
	  break;
	case lecteurSym::PIGMENT:
	  lirePigment (m);
	  break;
	case lecteurSym::FINISH:
	  lireFinish (m);
	  break;
	case lecteurSym::NORMAL:
	  lireNormal (m);
	  break;
	default:
	  afficherErreur ("parametre inconnu ");
	}
    }
  if (ls.codeSymboleCourant () == lecteurSym::FIN)
    afficherErreur ("il manque une accolade fermante ");
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireTransform (struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::TRANSFORM);

  if (ls.codeSymboleCourant () != lecteurSym::FIN
      && ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      while (ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
	{

	  switch (ls.codeSymboleCourant ())
	    {
	    case lecteurSym::ROTATE:
	      ls.sauterSymbole (lecteurSym::ROTATE);
	      lireTriplet (&rotate[0], &rotate[1],&rotate[2]);
	      for (int i = 0; i < 3; i++)
		rotate[i] *= M_PI / 180.0;
	      break;
	    case lecteurSym::SCALE:
	      ls.sauterSymbole (lecteurSym::SCALE);
	      lireTriplet (&scale[0], &scale[1],&scale[2]);
	      break;
	    case lecteurSym::TRANSLATE:
	      ls.sauterSymbole (lecteurSym::TRANSLATE);
	      lireTriplet (&translate[0], &translate[1],&translate[2]);
	      break;
	    default:
	      afficherErreur ("parametre transform inconnu ");
	    }
	}
      if (ls.codeSymboleCourant () == lecteurSym::FIN)
	afficherErreur ("il manque une accolade fermante ");
    }
  else
    afficherErreur ("il manque une accolade ouvrante  ");

  if (!ls.sauterSymbole (lecteurSym::ACCOLADE_FERMANTE))
    afficherErreur ("il manque une accolade fermante ");
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lirePigment (struct MODIFIER *m)
{

  char tmp[20];

  ls.sauterSymbole (lecteurSym::PIGMENT);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      while (ls.codeSymboleCourant () != lecteurSym::FIN
	     && ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
	{

	  switch (ls.codeSymboleCourant ())
	    {
	    case lecteurSym::COLOR:
	      ls.sauterSymbole (lecteurSym::COLOR);
	      lireTriplet (&(m->couleur[0]), &(m->couleur[1]),
			   &(m->couleur[2]));
	      m->typePigment = objet::COULEUR;
	      break;
	    case lecteurSym::TEXTURE:
	      lireTexture (m);
	      break;
	    case lecteurSym::CHECKER:
	      lireChecker (m);
	      break;
	    case lecteurSym::PERLIN:
	      ls.sauterSymbole (lecteurSym::PERLIN);
	      lirePerlin (m, PIGMENT);
	      break;
	    case lecteurSym::WOOD:
	      ls.sauterSymbole (lecteurSym::WOOD);
	      m->pNoise->setWood ();
	      lirePerlin (m, PIGMENT);
	      break;
	    case lecteurSym::MARBLE:
	      ls.sauterSymbole (lecteurSym::MARBLE);
	      m->pNoise->setMarble ();
	      lirePerlin (m, PIGMENT);
	      break;
	    case lecteurSym::ROTATE:
	      ls.sauterSymbole (lecteurSym::ROTATE);
	      lireTriplet (&rotatePm[0], &rotatePm[1],&rotatePm[2]);
	      for (int i = 0; i < 3; i++)
		rotatePm[i] *= M_PI / 180.0;
	      break;
	    case lecteurSym::SCALE:
	      ls.sauterSymbole (lecteurSym::SCALE);
              lireTriplet (&scalePm[0], &scalePm[1],&scalePm[2]);
	      break;
	    case lecteurSym::TRANSLATE:
	      ls.sauterSymbole (lecteurSym::TRANSLATE);
              lireTriplet (&translatePm[0],&translatePm[1],&translatePm[2]);
	      break;
	    default:
	      afficherErreur ("parametre pigment inconnu ");
	    }
	}
      if (ls.codeSymboleCourant () == lecteurSym::FIN)
	afficherErreur ("il manque une accolade fermante ");
    }
  else
    afficherErreur ("il manque une accolade ouvrante  ");

  if (!ls.sauterSymbole (lecteurSym::ACCOLADE_FERMANTE))
    afficherErreur ("il manque une accolade fermante ");

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireTexture (struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::TEXTURE);
  lireChaine (m->texture);
  m->mapper = new textureMapper (m->texture);

  if (!ls.sauterSymbole (lecteurSym::VIRGULE))
    afficherErreur ("il manque une virgule dans le triplet ");
  lireNombreInt (&freq);
  m->mapper->setFrequence (freq);
  m->typePigment = objet::TEXTURE_MAPPING;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireChecker (struct MODIFIER *m)
{

  char tmp[20];

  m->typePigment = objet::CHECKER;
  ls.sauterSymbole (lecteurSym::CHECKER);

  lireNombreFloat (&size);
  if (!ls.sauterSymbole (lecteurSym::VIRGULE))
    afficherErreur ("il manque une virgule dans le triplet ");
  lireTriplet (&couleur1[0], &couleur1[1], &couleur1[2]);
  if (!ls.sauterSymbole (lecteurSym::VIRGULE))
    afficherErreur ("il manque une virgule dans le triplet ");
  lireTriplet (&couleur2[0], &couleur2[1], &couleur2[2]);

  if (size < 0)
    size = 1.0;

  m->ccr->setSize (size);
  m->ccr->setCouleur1 (couleur1);
  m->ccr->setCouleur2 (couleur2);

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lirePerlin (struct MODIFIER *m, int type)
{


  char tmp[20];

  if (type == PIGMENT)
    m->typePigment = objet::PERLIN;
  else if (type == NORMAL)
    m->typeNormale = objet::PERLIN;

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      lireNombreFloat (&alpha);
      if (type == PIGMENT)
	m->pNoise->setAlpha (alpha);
      else if (type == NORMAL)
	m->pNormale->setAlpha (alpha);

      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule");

      lireNombreFloat (&beta);
      if (type == PIGMENT)
	m->pNoise->setBeta (beta);
      else if (type == NORMAL)
	m->pNormale->setBeta (beta);

      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule");

      lireNombreInt (&octave);
      if (type == PIGMENT)
	m->pNoise->setOctave (octave);
      else if (type == NORMAL)
	m->pNormale->setOctave (octave);

      if (!ls.sauterSymbole (lecteurSym::VIRGULE))
	afficherErreur ("il manque une virgule");

      lireNombreFloat (&intensite);
      if (type == PIGMENT)
	m->pNoise->setIntensite (intensite);
      else if (type == NORMAL)
	m->pNormale->setIntensite (intensite);

      while (ls.codeSymboleCourant () != lecteurSym::FIN
	     && ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
	{

	  switch (ls.codeSymboleCourant ())
	    {
	    case lecteurSym::SCALE:
	      ls.sauterSymbole (lecteurSym::SCALE);
	      if (type == NORMAL) 
		lireTriplet (&scaleN[0], &scaleN[1], &scaleN[2]);
	      else
		afficherErreur ("parametre SCALE interdit si le bruit de perlin est specifie dans PIGMENT");
	      break;
	    case lecteurSym::ROTATE:
	      ls.sauterSymbole (lecteurSym::ROTATE);
	      if (type == NORMAL) 
		lireTriplet (&rotateN[0], &rotateN[1], &rotateN[2]);
	      else
		afficherErreur ("parametre ROTATE interdit si le bruit de perlin est specifie dans PIGMENT");
	      break;
	    case lecteurSym::TRANSLATE:
	      ls.sauterSymbole (lecteurSym::TRANSLATE);
	      if (type == NORMAL) 
		lireTriplet (&translateN[0], &translateN[1], &translateN[2]);
	      else
		afficherErreur ("parametre TRANSLATE interdit si le bruit de perlin est specifie dans PIGMENT");
	      break;
	    case lecteurSym::COLOR_MAP:
	      if (type == PIGMENT)
		lireColorMap (m);
	      else
		afficherErreur("color_map interdit pour autre chose que la definition d'un pigment ");
	      break;
	    default:
	      afficherErreur ("parametre perlin inconnu ");
	    }
	}

      if (ls.codeSymboleCourant () == lecteurSym::FIN)
	afficherErreur ("il manque une accolade fermante ");
    }
  else
    afficherErreur ("il manque une accolade ouvrante  ");

  if (!ls.sauterSymbole (lecteurSym::ACCOLADE_FERMANTE))
    afficherErreur ("il manque une accolade fermante ");
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireColorMap (struct MODIFIER *m)
{

  double oldRg = 0.0;
  double rg;
  double coul[3];
  int nbCoul = 0;

  ls.sauterSymbole (lecteurSym::COLOR_MAP);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      while (ls.codeSymboleCourant () != lecteurSym::FIN
	     && ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
	{

	  switch (ls.codeSymboleCourant ())
	    {
	    case lecteurSym::CROCHET_OUVRANT:
	      ls.sauterSymbole (lecteurSym::CROCHET_OUVRANT);
	      lireNombreFloat (&rg);
	      if (nbCoul == 0 && rg != 0.0)
		afficherErreur
		  ("la table des couleurs doit commencer a 0.0 ");
	      if (rg > 1.0)
		afficherErreur
		  ("la table des couleurs ne doit pas depasser 1.0 ");
	      if (rg < oldRg)
		afficherErreur
		  ("les couleurs de la table des couleurs doivent etre ranges dans l'ordre ");
	      if (!ls.sauterSymbole (lecteurSym::COLOR))
		afficherErreur
		  ("il manque le mot cle COLOR apres une nouvelle entree dans la table des couleurs ");
	      lireTriplet (&(coul[0]), &(coul[1]), &(coul[2]));

	      if (!ls.sauterSymbole (lecteurSym::CROCHET_FERMANT))
		afficherErreur ("il manque un crochet fermant ");

	      for (int i = 0; i < 3; i++)
		colorMap[nbCoul][i] = coul[i];
	      range[nbCoul] = rg;

	      oldRg = rg;
	      nbCoul++;
	      break;
	    default:
	      afficherErreur ("parametre color_map inconnu ");
	    }
	}
      if (ls.codeSymboleCourant () == lecteurSym::FIN)
	afficherErreur ("il manque une accolade fermante ");
    }
  else
    afficherErreur ("il manque une accolade ouvrante  ");

  if (!ls.sauterSymbole (lecteurSym::ACCOLADE_FERMANTE))
    afficherErreur ("il manque une accolade fermante ");

  m->pNoise->setColorMap (nbCoul, colorMap, range);

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireFinish (struct MODIFIER *m)
{

  ls.sauterSymbole (lecteurSym::FINISH);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      while (ls.codeSymboleCourant () != lecteurSym::FIN
	     && ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
	{

	  switch (ls.codeSymboleCourant ())
	    {
	    case lecteurSym::AMBIENT:
	      ls.sauterSymbole (lecteurSym::AMBIENT);
	      lireNombreFloat (&(m->ambient));
	      break;
	    case lecteurSym::DIFFUSE:
	      ls.sauterSymbole (lecteurSym::DIFFUSE);
	      lireNombreFloat (&(m->diffuse));
	      break;
	    case lecteurSym::SPECULAR:
	      ls.sauterSymbole (lecteurSym::SPECULAR);
	      lireNombreFloat (&(m->specular));
	      break;
	    case lecteurSym::SHININESS:
	      ls.sauterSymbole (lecteurSym::SHININESS);
	      lireNombreFloat (&(m->shininess));
	      break;
	    case lecteurSym::TRANSPARENCY:
	      ls.sauterSymbole (lecteurSym::TRANSPARENCY);
	      lireNombreFloat (&(m->transparency));
	      break;
	    case lecteurSym::REFLECTION:
	      ls.sauterSymbole (lecteurSym::REFLECTION);
	      lireNombreFloat (&(m->reflection));
	      break;
	    case lecteurSym::IOR:
	      ls.sauterSymbole (lecteurSym::IOR);
	      lireNombreFloat (&(m->ior));
	      break;
	    default:
	      afficherErreur ("parametre finish inconnu ");
	    }
	}
      if (ls.codeSymboleCourant () == lecteurSym::FIN)
	afficherErreur ("il manque une accolade fermante ");
    }
  else
    afficherErreur ("il manque une accolade ouvrante  ");

  if (!ls.sauterSymbole (lecteurSym::ACCOLADE_FERMANTE))
    afficherErreur ("il manque une accolade fermante ");

  if (m->ambient < 0.0)
    m->ambient = 0.0;
  if (m->ambient > 1.0)
    m->ambient = 1.0;

  if (m->diffuse < 0.0)
    m->diffuse = 0.0;
  if (m->diffuse > 1.0)
    m->diffuse = 1.0;

  if (m->specular < 0.0)
    m->specular = 0.0;
  if (m->specular > 1.0)
    m->specular = 1.0;

  if (m->reflection < 0.0)
    m->reflection = 0.0;
  if (m->reflection > 1.0)
    m->reflection = 1.0;

  if (m->transparency < 0.0)
    m->transparency = 0.0;
  if (m->transparency > 1.0)
    m->transparency = 1.0;

  if (m->ior < 0.0)
    m->ior = 0.0;

  if (m->shininess < 0.0)
    m->shininess = 0.0;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireNormal (struct MODIFIER *m)
{
  char tmp[20];

  ls.sauterSymbole (lecteurSym::NORMAL);

  if (ls.sauterSymbole (lecteurSym::ACCOLADE_OUVRANTE))
    {

      while (ls.codeSymboleCourant () != lecteurSym::FIN
	     && ls.codeSymboleCourant () != lecteurSym::ACCOLADE_FERMANTE)
	{

	  switch (ls.codeSymboleCourant ())
	    {
	    case lecteurSym::PERLIN:
	      ls.sauterSymbole (lecteurSym::PERLIN);
	      lirePerlin (m, NORMAL);
	      break;
	    case lecteurSym::WOOD:
	      ls.sauterSymbole (lecteurSym::WOOD);
	      m->pNormale->setWood ();
	      lirePerlin (m, NORMAL);
	      break;
	    case lecteurSym::MARBLE:
	      ls.sauterSymbole (lecteurSym::MARBLE);
	      m->pNormale->setMarble ();
	      lirePerlin (m, NORMAL);
	      break;
	    default:
	      afficherErreur ("parametre normale inconnu ");
	    }
	}
      if (ls.codeSymboleCourant () == lecteurSym::FIN)
	afficherErreur ("il manque une accolade fermante ");
    }
  else
    afficherErreur ("il manque une accolade ouvrante  ");

  if (!ls.sauterSymbole (lecteurSym::ACCOLADE_FERMANTE))
    afficherErreur ("il manque une accolade fermante ");



}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireNombreFloat (double *n)
{

  float num;

  sscanf (ls.chaineSymboleCourant (), "%f", &num);

  if (ls.sauterSymbole (lecteurSym::NOMBRE))
    *n = (double) num;
  else
    afficherErreur ("un nombre est manquant ");
}

void
lecteurScene::lireNombreInt (int *n)
{
  float num;
  sscanf (ls.chaineSymboleCourant (), "%f", &num);

  if (ls.sauterSymbole (lecteurSym::NOMBRE))
    *n = (int) num;
  else
    afficherErreur ("un nombre est manquant ");
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireTriplet (double *n1, double *n2, double *n3)
{


  if (!ls.sauterSymbole (lecteurSym::CHEVRON_OUVRANT))
    afficherErreur ("il manque un chevron ouvrant ");
  lireNombreFloat (n1);
  if (!ls.sauterSymbole (lecteurSym::VIRGULE))
    afficherErreur ("il manque une virgule dans le triplet ");
  lireNombreFloat (n2);
  if (!ls.sauterSymbole (lecteurSym::VIRGULE))
    afficherErreur ("il manque une virgule dans le triplet ");
  lireNombreFloat (n3);
  if (!ls.sauterSymbole (lecteurSym::CHEVRON_FERMANT))
    afficherErreur ("il manque un chevron fermant ");

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurScene::lireChaine (char *c)
{

  strcpy (c, ls.chaineSymboleCourant ());
  if (!ls.sauterSymbole (lecteurSym::CHAINE))
    afficherErreur ("une chaine est manquante ");

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
