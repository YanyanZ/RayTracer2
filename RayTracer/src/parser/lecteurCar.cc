
/***************************************************************************************/
/*						                                       */
/* Realise par : 	BONFORT THOMAS		                                       */
/*		        CHAIGNEAU DELPHINE	                                       */
/*			GALIZZI OLIVIER			                               */
/*			HEIGEAS LAURE		                                       */
/*                                                                                     */
/* Date :		20/05/2001	                                               */
/*                                                                                     */
/* Commentaires : permet de lire un fichier caractere par caractere                    */
/*                                                                                     */
/***************************************************************************************/

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

#include "lecteurCar.h"

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

lecteurCar::lecteurCar (char nomFich[]):
ifstream (nomFich)
{

  if (fail ())
    {
      cout << endl;
      cout << "raytracer : *** Erreur [" << nomFich << "] :" << endl;
      cout << " \tFichier de description \"" << nomFich << "\" introuvable "
	<< endl;
      cout << endl;
      exit (0);
    }

  cout << endl << "\tOuverture du fichier \"" << nomFich << "\" ";
  cout << "\t [   OK   ]" << endl;

  numeroLigne = 0;
  uneLigne = (char *) malloc (1000 * sizeof (char));
  lireLigne ();
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

lecteurCar::~lecteurCar ()
{
  close ();
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

char
lecteurCar::peek ()
{

  return ligne.peek ();
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurCar::get (char &c)
{

  ligne.get (c);
  if (c == '\n')
    lireLigne ();
  if (fail ())
    c = '*';

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

void
lecteurCar::lireLigne ()
{

  char c = '.';
  int i = 0;

  ligne.seekp (0, ios::beg);
  ligne.seekg (0, ios::beg);

  numeroLigne++;
  while (!eof () && c != '\n')
    {
      ifstream::get (c);
      uneLigne[i++] = c;
      ligne.put (c);
    }

  uneLigne[i - 1] = '\0';


}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

int
lecteurCar::getNumeroLigneCourante ()
{
  return numeroLigne;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////

char *
lecteurCar::getLigneCourante ()
{

  return uneLigne;
}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
