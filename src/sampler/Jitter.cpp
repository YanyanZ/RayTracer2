# include <sampler/Jitter.hpp>

	
Jittered::Jittered()
  : Sampler()
{}

Jittered::Jittered(const int nb_samples)
  : Sampler(nb_samples)
{
  generate_samples();
}

Jittered::Jittered(const int nb_samples, const int nb_sets)
  : Sampler(num_samples, nb_sets)
{
  generate_samples();
}

Jittered::Jittered(const Jittered& j)
  : Sampler(j)
{
  generate_samples();
}

Jittered& Jittered::operator= (const Jittered& rhs)
{
  if (this == &rhs)
    return (*this);
  
  Sampler::operator= (rhs);

  return (*this);
}

Jittered* Jittered::clone() const
{
  return (new Jittered(*this));
}

Jittered::~Jittered(void) {}

void Jittered::generate_samples()
{	
  int n = (int) sqrt((float)num_samples); 
	
  for (int p = 0; p < num_sets; p++)
    for (int j = 0; j < n; j++)		
      for (int k = 0; k < n; k++) {
	Vector<float> sp((k + rand_float()) / n, (j + rand_float()) / n, 0);

	samples.push_back(sp);
      }		
}
