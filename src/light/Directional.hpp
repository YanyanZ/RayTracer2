/*!
 * \file Directional.hpp
 * \brief Classe pour les lumières directionnelles
 * \author Florian Thomassin, Victor Degliame
 * \version 1.1
 */

#ifndef DIRECTIONAL_HPP
# define DIRECTIONNAL_HPP

# include <object/Object.hpp>
# include <light/Light.hpp>

# include <tools/Ray.hpp>

using namespace Tools;
using namespace Form;

/*!
 * \namespace Lightning
 * Regourpe tous les types de lumières
 */
namespace Lightning
{
  /*!
   * \class Directional
   * \bref Classe pour les lumières directionnelles
   */
  class Directional : public Light
  {
  private:
    double direction[4]; /*!< Direction de la lumière */

  public:
   /*!
    * \brief Constructeur
    * Constructeur de la classe
    * \param dir : direction
    * \param c : couleur
    */
    Directional(double* dir, double* c);
    /*!
     * \brief Destructeur
     * Destructeur de la classe
     */
    virtual ~Directional(void);

  public:
    /*
     * \brief Récupère la direction
     */
    void getDirection(double dir[4]);
    /*!
     * \brief Récupère l'exposition
     */
    void getShiness(Ray* r, double p[4], double n[4], Object* o, double l[3]);
  };
}

#endif
