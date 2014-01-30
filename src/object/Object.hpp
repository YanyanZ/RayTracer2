/*!
 * \file Object.hpp
 * \brief Classe mère pour les objets
 * \author Florian Thomassin, Victor Degliame
 * \version 1.1
 */

#ifndef OBJET_HPP
# define OBJET_HPP

# include <values.h>
# include <cmath>
# include <stdlib.h>
# include <iostream>

# include <tools/Ray.hpp>

# include <texture/Checker.hpp>
# include <tools/Polynomial.hpp>
# include <texture/Mapper.hpp>
# include <tools/Transformer.hpp>

using namespace Tools;
using namespace Texture;

/*!
 * \namespace Form
 * Regroupe tous les objets affichables pour le rayracer
 */
namespace Form
{
  /*!
   * \class Object
   * \bref Classe mère des objets
   */
  class Object
  {
  public:
    /*!
     * \enum Type de pour les couleurs
     */
    enum {COLOR, TEXTURE, CHECKER, NO};

  protected:
    double epsilon;
    double rhoA;      /*!< Coefficient d'attenuation de la lumiere ambiente */
    double rhoD;      /*!< Coefficient d'attenuation de la lumiere directionnelle */
    double rhoS;      /*!< Coefficient attenuation de la lumiere speculaire */
    double rhoR;      /*!< Coefficient de réflection */
    double rhoT;      /*!< 1 - rhoR */
    double n;	      /*!< Indice de refraction de l'objet */
    double shiness;   /*!< Facteur de brillance */
    double c[3];      /*!< Couleur */
    int tPigment;     /*!< Type de pigments */
    int tNormal;      /*!< Type de normales */

  protected:
    Mapper *mapper;   /*!< Mapper pour la couleur */
    Checker *ccr;     /*!< Checker pour les couleurs */
    Transformer* trans; /*!< Outil pour les transformations de vecteurs*/

  public:
    /*!
     * \brief Constructeur
     * Constructeur de la classe
     */
    Object(void);
    /*!
     * \brief Destructeur
     * Destructeur de la classe
     */
    virtual ~Object(void);

  public:
    /*!
     * \brief Calcule de distances dentre deux points
     * \param p1 : premier point
     * \param p2 : deuxième point
     * \return Résultat de calcul de la distance
     */
    double distance(double* p1, double* p2);

  public:
    /*!
     * \brief Définie l'outils de transforamtion de vecteurs
     * \param trs : transformer
     */
    void setTransformer(Transformer* trs);
    /*!
     * \brief Définie epsilon
     * \param e : epsilon
     */
    void setEpsilon(double e);
    /*!
     * \brief Définie le coef rhoA
     * \param v : value
     */
    void setRhoA(double v);
    /*!
     * \brief Définie le coef rhoD
     * \param v : value
     */
    void setRhoD(double v);
    /*!
     * \brief Définie le coef rhoR
     * \param v : value
     */
    void setRhoR(double v);
    /*!
     * \brief Définie le coef rhoS
     * \param v : value
     */
    void setRhoS(double v);
    /*!
     * \brief Définie le coef rhoT
     * \param v : value
     */
    void setRhoT(double v);
    /*!
     * \brief Définie l'indice de réfraction
     * \param v : value
     */
    void setN(double v);
    /*!
     * \brief Définie la brillance
     * \param v : value
     */
    void setShininess(double v);
    /*!
     * \brief Définie le type de pigments
     * \param t : type
     */
    void setTypePigment(int t);
    /*!
     * \brief Définie la couleur
     * \param colo : couleur
     */
    void setColor(double colo[3]);
    /*!
     * \brief Définie le Checker
     * \param cc : pointeur vers le checker
     */
    void setChecker(Checker* cc);
    void setTypeNormal(int type);
    /*!
     * \brief Définie le mapper
     * \param mp : mapper de couleurs
     */
    void setMapper(Mapper* mp);

  public:
    /*!
     * \brief Récupérer epsilon
     * \return Valeur
     */
    double getEpsilon(void);
    /*!
     * \brief Récupérer rhoA
     * \return Valeur
     */
    double getRhoA(void);
    /*!
     * \brief Récupérer rhoD
     * \return Valeur
     */
    double getRhoD(void);
    /*!
     * \brief Récupérer rhoR
     * \return Valeur
     */
    double getRhoR(void);
    /*!
     * \brief Récupérer rhoS
     * \return Valeur
     */
    double getRhoS(void);
    /*!
     * \brief Récupérer rhoT
     * \return Valeur
     */
    double getRhoT(void);
    /*!
     * \brief Récupérer indice de réfraction
     * \return Valeur
     */
    double getN(void);
    /*!
     * \brief Récupérer brillance
     * \return Valeur
     */
    double getShininess(void);
    /*!
     * \brief Récupérer la couleur
     */
    void getColor(double p[4], double* c);
    void getChecker(double p[4], double c[3]);
    double getRefractionIndex(void);

  public:
    /*!
     * \brief Test s'il y a un rayon
     */
    bool tRay(Ray* r, double i[4], double normal[4], Ray* r2);
    /*!
     * \brief Test s'il y a un rayon
     */
    bool rRay(Ray* r, double i[4], double normal[4], Ray* r2);

  public:
    /*!
     * \brief Calcule l'intersection
     */
    virtual double hit(Ray* r, double i[4]);
    /*!
     * \brief Calcule la normale
     */
    virtual void normal(double p[4], Ray* r,
			double normal[4]);

  public:
    void checkNormal(double n[4], double p[4], Ray* r);
  };
}
#endif
