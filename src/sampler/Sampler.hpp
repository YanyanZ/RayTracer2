#ifndef SAMPLER_HPP__
# define SAMPLER_HPP__

# include <algorithm>
# include <vector>
# include <cmath>
# include <iostream>
# include <sstream>

# include <tools/Vector.hpp>

using namespace Tools;

class Sampler
{
protected:
  int num_samples;
  int num_sets;
  std::vector<int> shuffled_indices;
  std::vector<Vector<float> > samples;
  std::vector<Vector<float> > disk_samples;
  std::vector<Vector<float> > hemisphere_samples;
  std::vector<Vector<float> > sphere_samples;

protected:
  unsigned long count;
  int jump;

public:
  virtual ~Sampler();

public:
  Sampler();
  Sampler(const int nb);
  Sampler(const int nb, const int nb_sets);
  Sampler(const Sampler& s);

public:
  Sampler& operator=(const Sampler& s);
  void set_nb_sets(const int i);
  const int get_nb_samples() const;

public:
  virtual Sampler* clone() const{return nullptr;};
  virtual void generate_sample(void){};

public:
  void setup_shuffled_indices();
  void shuffle_x();
  void shuffle_y();
  void map_samples_to_unit_disk();
  void map_samples_to_hemisphere(const float p);
  void map_samples_to_sphere();

public:
  Vector<float> sample_unit_square();
  Vector<float> sample_unit_disk();
  Vector<float> sample_hemisphere();
  Vector<float> sample_sphere();
  Vector<float> sample_one_set();

public:
  float rand_float();

public:
  std::string print();
};

#endif
