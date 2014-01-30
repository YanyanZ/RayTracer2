/*!
 * \file Triangle.hpp
 * \brief Classe pour les triangles
 * \author Florian Thomassin, Victor Degliame
 * \version 1.1
 */

#ifndef TRIANGLE_HPP
# define TRIANGLE_HPP

# include <vector>

# include <object/Object.hpp>
# include <tools/Ray.hpp>
# include <tools/Transformer.hpp>

using namespace Tools;

/*!
 * \namespace Form
 * Regroupe tous les objets affichables pour le rayracer
 */
namespace Form
{
  /*!
   * \class Triangle
   * \bref Classe pour les objets (triangles)
   */
  class Triangle : public Object
  {
  private:
    double p1[4]; /*!< Sommet 1 */
    double p2[4]; /*!< Sommet 2 */
    double p3[4]; /*!< Sommet 3 */

  public:
    /*!
     * \brief Constructeur
     * Constructeur de classe
     * \param pp1 : sommet 1
     * \param pp2 : sommet 2
     * \param pp3 : sommet 3
     */
    Triangle(double pp1[4], double pp2[4], double pp3[4]);
    /*!
     * \brief Destructeur
     * Destructeur de classe
     */
    virtual ~Triangle(void);

  public:
    /*!
     * \brief Calcule l'intersection
     */
    double hit(Ray* r, double i[4]);
    /*!
     * \brief Calcule la normale
     */
    void normal(double p[4], Ray* r, double normal[4]);
  };
}

#endif // __TRIANGLE__
