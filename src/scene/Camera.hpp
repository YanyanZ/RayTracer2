/*!
 * \file Camera.hpp
 * \brief Camera pour le RayTracer
 * \author Florian Thomassin, Victor Degliame
 * \version 1.1
 */

#ifndef CAMERA_HPP
# define CAMERA_HPP

# include <iostream>
# include <cmath>

# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

using namespace Tools;

/*!
 * \namespace Engine
 * Regroupe les classes qui forment le coeur du Raytracer
 */
namespace Engine
{
  /*!
   * \class Camera
   * \brief classe representant la camera
   *
   *  La classe gère la camera de la scène
   */
  class Camera
  {
  public:
    /*!
     * \enum Camera Type
     * \brief Type de camera
     */
    enum {PERSPECTIVE, ORTHOGRAPHIC};

  private:
    double focal;       /*!< Focal de la camera */
    double position[4]; /*!< Position de la camera */
    double lookAt[4];   /*!< Direction de regard de la camera */
    double fov;         /*!< Champ de vision de la camera */
    int tProjection;    /*!< Type de projection */
    double sProjection; /*!< Taille de la projection */

  private:
    Transformer* trans; /*< Outils d'operation sur les vecteurs */

  public:
    /*!
     * \brief Constructeur
     * Constructeur de la classe
     * \param pos : position de la camera
     * \param lat : lookAt de la camera
     */
    Camera (double pos[4], double lat[4]);
    /*!
     * \brief Destructeur
     * Destructeur de la class
     */
    ~Camera(void);

  public:
    /*!
     * \brief Récupère la focal de la camera
     * Retourne la focal
     */
    const double getFocal(void);
    /*!
     * \brief Récupère le champ de vision de la camera
     * Retourne la FOV
     */
    const double getFov(void);
    /*!
     * \brief Récupère le type de projection de la camera
     * Retourne la TProjection
     */
    const int getTProjection(void);
    /*!
     * \brief Récupère la taille de la projection
     * Retourne la SProjection
     */
    const double getSProjection(void);

  public:
    /*!
     * \brief Met en place la class Transformation
     * Initialise la classe d'operateur sur les vecteurs
     */
    void setTransformation();
    /*!
     * \brief Défini la focal de la camera
     * \param f : focal
     */
    void setFocal(double f);
    /*!
     * \brief Défini la fov de la camera
     * \param f : champ de vision
     */
    void setFov(double f);
    /*!
     * \brief Défini le type de projection
     * \param tp : type de projection
     */
    void setTProjection (int tp);
    /*!
     * \brief Défini la taille de la projection
     * \param ps : taille de projection
     */
    void setSProjection(double ps);

  public:
    /*!
     * \brief Va permetre de recalculer le rayon en fonction de la camera
     * \param r : rayon d'origine
     * \param r2 : rayon re calculé
     */
    void rScene(Ray* r, Ray *r2);
  };
}

#endif
