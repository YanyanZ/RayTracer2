#ifndef JITTERED_HPP__
# define JITTERED_HPP__

# include <sampler/Sampler.hpp>

class Jittered : public Sampler
{
public:
  virtual ~Jittered();

public:
  Jittered();
  Jittered(const int nb_samples);
  Jittered(const int nb_samples, const int nb_sets);
  Jittered(const Jittered& j);

public:
  Jittered& operator= (const Jittered& rhs);

public:
  virtual Jittered* clone() const;
  virtual void generate_samples();
};

#endif
