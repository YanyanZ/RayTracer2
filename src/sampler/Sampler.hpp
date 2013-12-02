#ifndef SAMPLER_HPP
# define SAMPLER_HPP

# include <vector>
# include <algorithm>
# include <random>
# include <iterator>

# include <tools/Vector.hpp>

using namespace Tools;

namespace Sampler
{
  class Sampler
  {
  public:
    int num_samples;
    int num_sets;
    unsigned long count;
    int jump;

  public:
    std::vector<Vector<float> > samples;
    std::vector<int> shuffled_indices;
    std::vector<Vector<float> > disk_samples;
    std::vector<Vector<float> > hemisphere_samples;
    std::vector<Vector<float> > sphere_samples;

  public:
    ~Sampler();

  public:
    Sampler();
    Sampler(const int num);
    Sampler(const int num, const int numsts);
    Sampler(const Sampler& s);

  public:
    virtual Sampler* clone() const = 0;

  public:
    Sampler& operator=(const Sampler& s);

  public:
    void shuffle_x_coordinates();
    void shuffle_y_coordinates();
    void setup_shuffled_indices();
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
    virtual void generate_samples() = 0;
  };
}

#endif
