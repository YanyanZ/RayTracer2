/*!
 * \file Light.hpp
 * \brief Classe mère pour les lumières
 * \author Florian Thomassin, Victor Degliame
 * \version 1.1
 */

#ifndef LIGHT_HPP
# define LIGHT_HPP

# include <iostream>
# include <values.h>
# include <stdlib.h>

# include <object/Object.hpp>
# include <tools/Ray.hpp>

using namespace Tools;

/*!
 * \namespace Lightning
 * Regourpe tous les types de lumières
 */
namespace Lightning
{
  /*!
   * \class Light
   * \bref Classe qui mère pour les lumières
   */
  class Light
  {
  protected:
    double color[4]; /*!< Couleur de la lumière */

  public:
    /*!
     * \brief Constructeur
     * Constructeur de la classe
     * \param c : couleur
     */
    Light(double* c);
    /*!
     * \brief Destructeur
     * Destructeur de la classe
     */
    virtual ~Light(void);

  public:
    /*!
     * \brief Permet de normaliser un vecteur pour les lumières
     * \param v : vecteur a normaliser
     */
    void normalize(double v[4]);
    /*!
     * \brief Produit scalaire
     * \param p1 : vecteur 1
     * \param p2 : vecteur 2
     * \result retrourne le resultat de l'opération
     */
    double dot(double p1[4], double p2[4]);

  public:
    /*!
     * \brief Récupère la couleur de la lumière
     * \param c : couleur (récupération par memcpy)
     */
    void getColor(double c[3]);
  };
}

#endif
