# include <parser/lecteurScene.h>
# include <Scene/Tracer.hpp>

int main (int argc, char *argv[])
{
  switch (argc)
    {
    case 1:
      cout << endl;
      cout << "raytracer : *** Erreur  :" << endl;
      cout << " \tIl manque des parammetres (fichier d'entree et de sortie)"
	<< endl;
      cout << "\tUtilisation : raytracer inputFile outputFile" << endl;
      cout << endl;
      exit (0);
      break;
    case 2:
      cout << endl;
      cout << "raytracer : *** Erreur  :" << endl;
      cout << " \tIl manque des parammetres (fichier de sortie)" << endl;
      cout << "\tUtilisation : raytracer inputFile outputFile" << endl;
      cout << endl;
      exit (0);
    case 3:
      break;
    default:
      cout << endl;
      cout << "raytracer : *** Erreur  :" << endl;
      cout << " \tIl y a trop de parametres" << endl;
      cout << "\tUtilisation : raytracer inputFile outputFile" << endl;
      cout << endl;
      exit (0);
      break;
    }

  /* lecture et recuperation de la description de la scene */
  lecteurScene ls (argv[1]);

  /* creation du tracer pour rendre la scene */
  tracer t (ls.getScene ());

  /* lancement du rendu de la scene */
  t.rendreScene ();

  /* sauvegarde de la scene dans le fichier de sortie */
  t.sauvegarderScene (argv[2]);


  return 1;

}

/////////////////////////////////////////////////////////////////////////////////////////
/////////////////////////////////////////////////////////////////////////////////////////
