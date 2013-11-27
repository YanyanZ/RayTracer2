# include <RayTracer.hpp>

int main(int argc, char* argv[])
{
  RayTracer* rt;

  if (argc != 3)
  {
    std::cerr << "[ERROR] Bad usage: ./RayTracer scene_descriptor output" << std::endl;

    return -1;
  }

  rt = new RayTracer(argv[1], argv[2]);
  if (rt == NULL)
  {
    std::cerr << "[ERROR] Failed to allocate memory to RayTracer - main.cpp: line 14";
    return -1;
  }

  rt->build();
  rt->trace();
  rt->save();

  delete rt;

  std::cout << "[INFO] Process end" << std::endl;

  return 0;
}
