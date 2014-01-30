/*!
 * \file Scene.hpp
 * \brief Classe principale, elle représente la scène principale
 * \author Florian Thomassin, Victor Degliame
 * \version 1.1
 */

#ifndef SCENE_HPP
# define SCENE_HPP

# include <cstdlib>
# include <vector>

# include <object/Object.hpp>
# include <scene/Camera.hpp>

# include <light/Ambiant.hpp>
# include <light/Point.hpp>
# include <light/Directional.hpp>

using namespace Tools;
using namespace Lightning;

/*!
 * \namespace Engine
 * Regroupe les classes qui forment le coeur du Raytracer
 */
namespace Engine
{
  /*!
   * \class Scene
   * \brief Classe regroupant toutes les information de scène
   */
  class Scene
  {
  private:
    std::vector<Object*>* objects;      /*!< Liste des objets */
    std::vector<Directional*>* dLights; /*!< Liste des lumière directionnelles */
    std::vector<Point*>* pLights;       /*!< Liste des lumière ponctuelles */
    double cBackground[3];              /*!< Couleur du fond */
    Ambiant* aLight;                    /*!< Couleur de la lumière ambiante */
    Camera* cam;                        /*!< Camera de la scène */

  private:
    int nbDirectional;  /*!< Nombre de lumières directionnelles */
    int nbPoint;        /*!< Nombre de lumières pontuelles */
    int nbObject;       /*!< Nombre d'objets */
    int maxTraceLevel;  /*!< Profondeur de lancer */
    int antialiasing;   /*!< Antialiasing */
    double aaThreshold; /*!< Pas de l'antialiasing */
    int oHeight;        /*!< Hauteur de l'image de sortie */
    int oWidth;         /*!< Largeur de l'image de sortie */
    double softShadow;    /*!< Activation des ombres */
    bool modeSoftShadow;  /*!< Activation des ombres */
    int nbShadowRay;      /*!< Nombre de rayons lancés pour les ombres */

  public:
   /*!
    * \brief Constructeur
    * Constructeur de la classe
    */
    Scene(void);
   /*!
    * \brief Destructeur
    * Destructeur de la classe
    */
    virtual ~Scene(void);

  public:
    /*!
     * \brief Ajoute un objet
     * \param o : pointeur sur un objet
     */
    void addObject(Object* o);
    /*!
    * \brief Change la camera
    * \param c : pointeur sur la nouvelle camera
    */
    void changeCamera(Camera* c);
    /*!
     * \brief Ajoute une lumière ambiante
     * \param l : pointeur sur la nouvelle lumière ambiante
     */
    void addAmbiant(Ambiant* l);
    /*!
     * \brief Ajoute une lumière directionnelle
     * \param l : pointeur sur la nouvelle lumière directionnelle
     */
    void addDirectional(Directional* l);
    /*!
     * \brief Ajoute une lumière ponctuelle
     * \param l : pointeur sur la nouvelle lumière directionnelle
     */
    void addPoint(Point* l);

  public:
    /*!
     * \brief Test s'il y a une illumination ponctuelle
     * \param p : point
     * \param nlum : nombre de lumières
     * \return Si le test est vérifié true sinon false
     */
    bool isPointRadiance(double* p, int nlum);
    /*!
     * \brief Test s'il y a une illumination directionelle
     * \param p : point
     * \param nlum : nombre de lumières
     * \return Si le test est vérifié true sinon false
     */
    bool isDirectionalRadiance(double* p, int nlum);

  public:
    /*!
     * \brief Récupère la camera
     * \return Pointeur sur la camera
     */
    Camera* getCamera(void);
    /*!
     * \brief Récupère l'objet i
     * \param i : id de l'objet
     * \return Pointeur sur l'objet
     */
    Object* getObject(int i);
    /*!
     * \brief Récupère la lumière ponctuelle i
     * \param i : id de la lumière
     * \return Pointeur sur la lumière
     */
    Point* getPoint(int i);
    /*!
     * \brief Récupère la lumière directionnelle i
     * \param i : id de la lumière
     * \return Pointeur sur la lumière
     */
    Directional* getDirectional(int i);
    /*!
     * \brief Récupère le nombre d'objet
     * \return Nombre d'objet
     */
    const int getNbObjects(void);
    /*!
     * \brief Récupère le nombre de lumières ponctuelles
     * \return Nombre de lumière
     */
    const int getNbPoints(void);
    /*!
     * \brief Récupère le nombre de lumière directionnelle
     * \return Nombre de lumière
     */
    const int getNbDirectionals(void);
    /*!
     * \brief Récupère la couleur de la lumière ambiante
     * \param amb : couleur (récupération par memcopy)
     */
    void getAmbiant(double amb[]);
    /*!
     * \brief Récupère le nombre de rayon pour les ombres
     * \return Nombre de rayons
     */
    const int getNbShadowRay(void);
    /*!
     * \brief Récupère la profondeur de tracer
     * \return Valeur
     */
    const int getMaxTraceLevel(void);
    /*!
     * \brief Récupère le niveau de l'antialiasing
     * \return Niveau de l'antialiasing
     */
    const int getAntialiasing(void);
    /*!
     * \brief Récupère le pas de l'antialiasing
     * \return Le pas
     */
    const double getAAThreshold(void);
    /*!
     * \brief Récupère la taille en hauteur de l'image de sortie
     * \return Hauteur
     */
    const int getOutputHeight(void);
    /*!
     * \brief Récupère la taille en largeur de l'image de sortie
     * \return Largeur
     */
    const int getOutputWidth(void);
    /*!
     * \brief Récupère la couleur du fond
     * \return couleur
     */
    const double* getBackground(void);

  public:
    /*!
     * \brief Définit la couleur du fond
     * \param Couleur du fond
     */
    void setBackground(double* c);
    /*!
     * \brief Définit des paramètres de la classe
     * \param mtl : max trace level
     * \param antil : niveau d'antialiasing
     * \param aath : pas de l'antialiasing
     * \param ss : ombres
     * \param nbss : nombre de rayons pour les ombres
     * \param oh : hauteur de l'output
     * \param ow : largeur de l'output
     */
    void setGlobalSetting(int mtl, int antil,  double aath,
			  double ss, int nbss, int oh, int ow);
  };
}

#endif
