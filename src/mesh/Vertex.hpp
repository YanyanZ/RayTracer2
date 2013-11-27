#ifndef VERTEX_HPP
# define VERTEX_HPP

# include <tools/Vector.hpp>

using namespace Tools;

struct VertexUV
{
  Vector<float> vertex;
  Vector<float> uv;      // Vecteur 2
};

struct VertexN
{
  Vector<float> vertex;
  Vector<float> normal;
};

struct VertexUVN
{
  Vector<float> vertex;
  Vector<float> normal;
  Vector<float> uv;      // Vecteur 2
};

#endif
