/*!
 * \file Plan.hpp
 * \brief Classe pour les plan
 * \author Florian Thomassin, Victor Degliame
 * \version 1.1
 */

#ifndef PLAN_HPP
# define PLAN_HPP

# include <object/Object.hpp>
# include <tools/Transformer.hpp>
# include <tools/Ray.hpp>

using namespace Tools;

/*!
 * \namespace Form
 * Regroupe tous les objets affichables pour le rayracer
 */
namespace Form
{
  /*!
   * \class Plan
   * \bref Classe pour les objets (plan)
   */
  class Plan : public Object
  {
  public:
    /*!
     * \brief Constructeur
     * Constructeur de classe
     */
    Plan(void);
    /*!
     * \brief Destructeur
     * Destructeur de classes
     */
    virtual ~Plan(void);

  public:
    /*!
     * \brief Calcule l'intersection
     */
    virtual double hit(Ray* r, double i[4]);
    /*!
     * \brief Calcule la normale
     */
    virtual void normal(double p[4], Ray* r, double normal[4]);
  };
}

#endif
