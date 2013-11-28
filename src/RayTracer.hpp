#ifndef RAYTRACER_HPP
# define RAYTRACER_HPP

# include <sstream>
# include <iostream>
# include <vector>
# include <string>

# include <engine/objects/Shape.hpp>
# include <engine/objects/basic/Sphere.hpp>
# include <engine/objects/basic/Triangle.hpp>
# include <display/Image.hpp>

# include <parser/xml/src/pugixml.hpp>

class RayTracer
{
private:
  std::string in;
  std::string out;

private:
  std::vector<std::vector<RGBColor<float> > > im;

private:
  int width;
  int heigh;
  std::vector<Objects::Basic::Sphere>* spheres;
  std::vector<Objects::Basic::Triangle>* triangles;

public:
  ~RayTracer();

public:
  RayTracer(std::string _in, std::string _out);

public:
  void build();
  void trace();
  void save();

};

#endif
