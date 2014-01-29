//# include <parser/SceneParser.hpp>
# include <scene/Tracer.hpp>

int main (int argc, char *argv[])
{
  if (argc == 3)
  {
    /* lecture et recuperation de la description de la scene */
    SceneParser ls (argv[1]);
    ls.parse();

    /* creation du tracer pour rendre la scene */
    Engine::Tracer t (ls.s());

    /* lancement du rendu de la scene */
    t.createScene ();

    /* sauvegarde de la scene dans le fichier de sortie */
    t.saveScene (argv[2]);

    return 1;
  }
  else
  {
    std::cerr << "[RAYTRACER][ERROR] - Bad usage - ./exe sceneDescriptor.xml outfile";
    std::cerr << std::endl;
    return -1;
  }
}
