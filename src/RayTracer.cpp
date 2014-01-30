# include <parser/SceneParser.hpp>

using namespace Engine;
using namespace Tools;
using namespace Lightning;
using namespace Form;

int main (int argc, char *argv[])
{
  if (argc == 3)
  {
    /* lecture et recuperation de la description de la scene */
    SceneParser sp(argv[1]);
    sp.parse();

    Scene* s = sp.getScene();

    Tracer* t = new Tracer(s);

    /* lancement du rendu de la scene */
    t->createScene ();

    /* sauvegarde de la scene dans le fichier de sortie */
    t->saveScene (argv[2]);

    return 1;
  }
  else
  {
    std::cerr << "[RAYTRACER][ERROR] - Bad usage - ./exe sceneDescriptor.xml outfile";
    std::cerr << std::endl;
    return -1;
  }
}

