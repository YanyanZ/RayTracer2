/*!
 * \file Tracer.hpp
 * \brief Système de lancé de rayons
 * \author Florian Thomassin, Victor Degliame
 * \version 1.1
 */

#ifndef TRACER_HPP
# define TRACER_HPP

# include <cmath>
# include <values.h>
# include <stdlib.h>
# include <fstream>

# include <object/Object.hpp>
# include <scene/Camera.hpp>
# include <light/Light.hpp>
# include <scene/Scene.hpp>

# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

# define maxVal 255

using namespace Tools;
using namespace Form;

/*!
 * \namespace Engine
 * Regroupe les classes qui forment le coeur du Raytracer
 */
namespace Engine
{
  /*!
   * \class Tracer
   * \brief classe permetant le lancer de rayons
   *
   *  La classe va lancer les rayons et calculer les intersections
   */
  class Tracer
  {
  private:
    Scene* s;          /*!< Classe de la scène */
    double pheight;    /*!< Hauteur recalculée */
    double pwidth;     /*!< Largeur recalculée */
    double pasx;       /*!< Pas de déplacement sur l'axe x */
    double pasy;       /*!< Pas de déplacement sur l'axe y */

  private:
    double aLight[3];      /*!< Couleur de la lumière ambiante */
    double cBackground[3]; /*!< Couleur du fond */

  private:
    double nbThrowRay;   /*!< Nombre de rayons lancés */
    int width;           /*!< Largeur d'origine */
    int height;          /*!< Hauteur d'origine */
    unsigned char *map;  /*!< Buffeur de l'image au format ppm */

  public:
    /*!
     * \brief Constructeur
     * Constructeur de la classe
     * \param s : scène
     */
    Tracer(Scene* s);
    /*!
     * \brief Destructeur
     * Destructeur de la classe
     */
    ~Tracer(void);

  public:
    /*!
     * \brief Définit la couleur d'un pixel
     * Permet de définir la couleur d'un pixel dans le buffer
     * \param x : coordonnée en x
     * \param y : coordonéee en y
     * \param c : couleur
     */
    void setPixel (int x, int y, double c[3]);
    /*!
     * \brief Récupère la couleur d'un pixel
     * Permet de récupérer la couleur d'un pixel dans le buffer
     * \param x : coordonnée en x
     * \param y : coordonéee en y
     * \param c : couleur (récupéré par memcpy)
     */
    void getPixel (int x, int y, double c[3]);

  public:
    /*!
     * \brief Initialise un rayon
     * \param x : coordonnée en x
     * \param y : coordonéee en y
     * \param r : rayon
     */
    void initRay(double x, double y, Ray *r);
    /*!
     * \brief Lance un rayon
     * \param r : rayon
     * \param deep : profondeur max du lancé
     * \param coul : couleur
     */
    void throwRay(Ray *r, int deep, double coul[3]);
    /*!
     * \brief Lance tous les rayons
     * \param i : coordonnée en x
     * \param j : coordonéee en y
     * \param c : couleur
     */
    void throwRays(int i, int j, double coul[3]);

  public:
    /*!
     * \brief Détermine si un rayon a touché un objet
     * \param r : rayon
     * \param hit : coordonné de l'intersection (récuperation par memcpy)
     * \param o : objet testé
     * \return Distance si contact
     */
    double evalHit(Ray* r, double hit[4], Object** o);
    /*!
     * \brief Détermine la couleur du la luminosité directe
     * \param r : rayon
     * \param o : objet
     * \param hit : coordonné de l'intersection
     * \param normal : normale
     * \param coul : couleur que l'on récupère
     */
    void evalDirectRadiance (Ray* r, Object* o, double hit[4],
			     double normal[4], double coul[3]);
    /*!
     * \brief Détermine la couleur du la luminosité réfléchie
     * \param r : rayon
     * \param o : objet
     * \param hit : coordonné de l'intersection
     * \param deep : profondeur de lancé
     * \param coul : couleur que l'on récupère
     */
    void evalReflectRadiance(Ray* r, Object* o, double hit[4],
			     double normal[4], int deep, double coul[3]);
    /*!
     * \brief Détermine la couleur du la luminosité transmise
     * \param r : rayon
     * \param o : objet
     * \param hit : coordonné de l'intersection
     * \param deep : profondeur de lancé
     * \param coul : couleur que l'on récupère
     */
    void evalSendRadiance(Ray* r, Object* o,
			  double hit[4],
			  double normal[4],
			  int deep,
			  double coul[3]);
    /*!
     * \brief Détermine la couleur du la luminosité ambiante
     * \param o : objet
     * \param p : point
     * \param coul : couleur que l'on récupère
     */
    void evalAmbiantRadiance(Object* o,
			     double p[3],
			     double coul[3]);

  public:
    /*!
     * \brief Permet de créer la scène en lançant les rayons
     */
    void createScene(void);
    /*!
     * \brief Permet de sauvegarder la scène dans une image ppm
     */
    void saveScene(std::string output);
  };
}

#endif
