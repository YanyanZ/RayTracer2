#ifndef MAPPER_HPP
# define MAPPER_HPP

# include <stdlib.h>
# include <string.h>
# include <cmath>
# include <fstream>

# include <tools/Transformer.hpp>

namespace Texture
{
  class Mapper
  {
  private:
  // le fichier d'entrée au format ppm P6
    std::ifstream * fichier;

    // le nom du fichier d'entrée
    char nomFichier[50];

    // le buffer de l'image
    unsigned char *map;

    // les dimensions et l'intensité maximum de l'image à mapper
    int width, height, intensity;
    int frequence;

    void remplirMap ();
    void erreur (char *texte);
    char getChar ();
    unsigned char getByte ();
    int getInt ();

    void getMappingPlan (double p[4], double coulobj[3]);
    void getMappingSphere (double p[4], double coulobj[3]);
    enum { PLAN, SPHERE, INDEFINI };
    int typeObjet;
    double rayonSphere;

    Transformer* trans;

  public:
    Mapper (char nomFichier[]);
    Mapper ();
    virtual ~ Mapper ();
    void getCouleurTexture (int i, int j, double couleur[3]);
    void getMapping (double p[4], double coulobj[3]);
    void setTexturePlan ();
    void setTextureSphere (double rayon);
    void setFrequence (int f);
    void setTransformer(Transformer * trans);
  };
}

#endif
