/*!
 * \file Point.hpp
 * \brief Classe pour les lumières ponctuelles
 * \author Florian Thomassin, Victor Degliame
 * \version 1.1
 */

#ifndef POINT_HPP
# define POINT_HPP

# include <cstring>
# include <cstdio>

# include <light/Light.hpp>
# include <object/Object.hpp>

using namespace Form;
using namespace Tools;

/*!
 * \namespace Lightning
 * Regourpe tous les types de lumières
 */
namespace Lightning
{
  /*!
   * \class Point
   * \bref Classe pour les lumières ponctuelles
   */
  class Point : public Light
  {
  private:
    double position[4];  /*!< Position de la lumière */
    double c1, c2, c3;   /*!< Coefficient d'atténuations */

  public:
    /*!
     * \brief Constructeur
     * Constructeur de la classe
     * \param pos : position
     * \param c : couleur
     */
    Point(double *pos, double* c);
    /*!
     * \brief Destructeur
     * Destructeur de la classe
     */
    virtual ~Point(void);

  public:
    /*!
     * \brief Définit les coefficients d'attenuations
     * \param cc1 : coef 1
     * \param cc2 : coef 2
     * \param cc3 : coef 3
     */
    void setDimming(double cc1,double cc2,double cc3);

  public:
    /*!
     * \brief Récupère le coef c1
     * \resultat coef c1
     */
    const double getC1 (void);
    /*!
     * \brief Récupère le coef c2
     * \resultat coef c2
     */
    const double getC2 (void);
    /*!
     * \brief Récupère le coef c3
     * \resultat coef c3
     */
    const double getC3 (void);

  public:
    /*!
     * \brief Récupère l'exposition
     */
    void getShiness(Ray* r, double p[4], double n[4], Object* o, double l[3]);
    /*
     * \brief Récupère la position
     */
    void getPosition (double pos[4]);
  };
}
#endif
