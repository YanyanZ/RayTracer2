/*!
 * \file Ambiant.cpp
 * \brief Lumière ambiante
 * \author Florian Thomassin, Victor Degliame
 * \version 1.1
 */

#ifndef AMBIANT_HPP
# define AMBIANT_HPP

# include <light/Light.hpp>

/*!
 * \namespace Lightning
 * Regroupe tous les types de lumières
 */
namespace Lightning
{
  /*!
   * \class Ambiant
   * \bref Classe pour la lumière ambiante
   */
  class Ambiant : public Light
  {
  public:
    /*!
     * \brief Constructeur
     * Constructeur de la classe
     * \param c : couleur
     */
    Ambiant(double c[3]);
    /*!
     * \brief Destructeur
     * Destructeur de la classe
     */
    virtual ~Ambiant(void);
  };
}

#endif
