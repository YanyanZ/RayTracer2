#ifndef RAYTRACER_HPP
# define RAYTRACER_HPP

// STL lib

# include <sstream>
# include <iostream>
# include <vector>
# include <string>

// Shapes libs

# include <engine/objects/Shape.hpp>
# include <engine/objects/basic/Sphere.hpp>
# include <engine/objects/basic/Triangle.hpp>

// Cameras libs

# include <cameras/Camera.hpp>

// Lights libs

# include <lights/Directional.hpp>

// Dispkay libs

# include <display/Image.hpp>

// Parser XML & OBJ

# include <parser/xml/src/pugixml.hpp>

// Class

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

private:
  std::vector<Objects::Shape*>* objects;
  std::vector<Light>* lights;

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
