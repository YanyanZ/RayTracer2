#ifndef RAYTRACER_HPP
# define RAYTRACER_HPP

# include <iostream>

# include <engine/Engine.hpp>

class RayTracer
{
private:
  std::string in;
  std::string out;

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
