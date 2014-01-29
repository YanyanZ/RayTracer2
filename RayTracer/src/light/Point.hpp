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
    void setDimming(double cc1,double cc2,double cc3);

  public:
    const double getC1 (void);
    const double getC2 (void);
    const double getC3 (void);

  public:
    void getShiness(Ray* r,
		    double p[4],
		    double n[4],
		    Object* o,
		    double l[3]);
    void getPosition (double pos[4]);
  };
}
#endif
