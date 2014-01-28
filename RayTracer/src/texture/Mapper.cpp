# include <texture/Mapper.hpp>

using namespace Texture;

Mapper::Mapper (char nomFichier[])
{
  fichier = new ifstream (nomFichier);
  if (fichier->fail ())
    erreur ("Erreur d'ouverture de fichier.");

  strcpy (this->nomFichier, nomFichier);

  typeObjet = INDEFINI;

  remplirMap ();
}

Mapper::Mapper ()
{
  typeObjet = INDEFINI;
}

Mapper::~Mapper ()
{
  free (map);
}

void
Mapper::erreur (char *texte)
{
  cout << endl;
  cout << "Texture Mapping : *** Erreur [" << nomFichier << "] :" << endl;
  cout << " \t" << texte << endl;
  cout << endl;
  exit (0);
}

void
Mapper::remplirMap ()
{

  char c;
  int n;

  //lecture du magic number
  c = getChar ();
  if (c != 'P')
    erreur ("Erreur de lecture du format.");
  n = getInt ();
  if (n != 6)
    erreur ("Erreur de lecture du format.");

  //lecture des dimensions et de l'intensité maximum
  width = getInt ();
  height = getInt ();
  intensity = getInt ();

  //allocation mémoire de la map
  map =
    (unsigned char *) malloc (3 * height * width * sizeof (unsigned char));

  //lecture des couleurs
  for (int i = 0; i < height; i++)
    for (int j = 0; j < width; j++)
      {
	for (int k = 0; k < 3; k++)
	  {
	    map[(i * width + j) * 3 + k] = getByte ();
	  }
      }
  fichier->close ();
}

char
Mapper::getChar ()
{
  char c;

  fichier->get (c);
  if (c == '#')
    {
      do
	{
	  fichier->get (c);
	}
      while (c != '\n' && c != '\r');
    }
  if (fichier->fail ())
    erreur ("Erreur de lecture de caractère.");
  return c;
}

unsigned char
Mapper::getByte ()
{
  char tmp;
  unsigned char c;

  fichier->get (tmp);
  c = (unsigned char) tmp;
  if (fichier->fail ())
    erreur ("Erreur de lecture d'octet.");
  return c;
}

int
Mapper::getInt ()
{
  int i;
  char c;

  do
    {
      c = getChar ();
    }
  while (c == ' ' || c == '\t' || c == '\n' || c == '\r');
  if (c < '0' || c > '9')
    erreur ("Erreur de lecture d'entier.");

  i = 0;
  do
    {
      i = i * 10 + c - '0';
      c = getChar ();
    }
  while (c >= '0' && c <= '9');

  return i;
}

void
Mapper::setFrequence (int f)
{
  frequence = f;
}

void
Mapper::setTexturePlan ()
{
  typeObjet = PLAN;
}

void
Mapper::setTextureSphere (double rayon)
{
  typeObjet = SPHERE;
  rayonSphere = rayon;
}

void Mapper::setTransformer(Transformer * trans){
  this->trans=trans;
}

void
Mapper::getCouleurTexture (int i, int j, double couleur[3])
{
  for (int k = 0; k < 3; k++)
    couleur[k] =
      (double) (map[((height - i - 1) * width + j) * 3 + k]) /
      ((double) intensity);
}

void
Mapper::getMapping (double p[4], double coulobj[3])
{
  double p2[4];

 trans->doTransformation(p2,p);

  switch (typeObjet)
    {
    case PLAN:
      getMappingPlan (p2, coulobj);
      break;
    case SPHERE:
      getMappingSphere (p2, coulobj);
      break;
    default:
      break;
    }

}

void
Mapper::getMappingPlan (double p[4], double coulobj[3])
{

  double u, v, t;
  double m;			//taille de l'image en hauteur
  int i, j;


  //calcul du pixel(i,j) correspondant à (y,z), frequence = taille de l'image en largeur
  t = ((int) ((p[1]-frequence/2) /(double)frequence)) * frequence;
  j = (int) (width * ((p[1]-frequence/2) - t) / frequence);
  if (j<0) j=width+j;


  m = (double) frequence *(double) height / (double) width;
  t = ((int) ((p[2]+m/2) / m)) * m;
  i = (int) (height * ((p[2]+m/2) - t) / m);
  if (i<0) i=height+i;

  getCouleurTexture (i, j, coulobj);

}

void
Mapper::getMappingSphere (double p[4], double coulobj[3])
{

  double u, v, t;
  int i, j;
  double ac;

  // Calul de u et de v tels que : (x, y, z) = (r*sinu,r*cosu*sinv, r*cosu*cosv)
  u = asin (p[0] / rayonSphere);	//u est dans [-pi/2;pi/2]
  if (cos (u) != 0.0)
    {
      ac = p[2] / (rayonSphere * cos (u));
      if (ac<-1) ac=-1;
      if (ac>1) ac=1;
      v = acos (ac);
    }
  else
    v = 0.0;

  if (p[1] > 0.0)
    v = - v;
  //v est dans [0;2pi[
  v+=M_PI;
  //calcul du pixel(i,j) correspondant à (u,v)
  t = (double) frequence *(u / M_PI + 0.5);
  i = (int) (height * (t - (int) t));

  t = 0.5 * (double) frequence *v / M_PI;
  j = (int) (width * (t - (int) t));
  getCouleurTexture (i, j, coulobj);
}
