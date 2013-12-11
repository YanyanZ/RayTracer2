# include <sampler/Sampler.hpp>

Sampler::~Sampler()
{
}

Sampler::Sampler()
  : num_samples (1),
    num_sets (83),
    count (0),
    jump (0)
{
  samples.reserve(num_samples * num_sets);
  setup_shuffled_indices();
}

Sampler::Sampler(const int nb)
  : num_samples (nb),
    num_sets (83),
    count (0),
    jump (0)
{
  samples.reserve(num_samples * num_sets);
  setup_shuffled_indices();
}

Sampler::Sampler(const int nb, const int nb_sets)
  : num_samples (nb),
    num_sets (nb_sets),
    count (0),
    jump (0)
{
  samples.reserve(num_samples * num_sets);
  setup_shuffled_indices();
}


Sampler::Sampler(const Sampler& s)				
  : num_samples(s.num_samples),
    num_sets(s.num_sets),
    shuffled_indices(s.shuffled_indices),
    samples(s.samples),
    disk_samples(s.disk_samples),
    hemisphere_samples(s.hemisphere_samples),
    sphere_samples(s.sphere_samples),
    count(s.count),
    jump(s.jump)
{
}

Sampler& Sampler::operator= (const Sampler& s)
{
  if (this == &s)
    return (*this);
	
  num_samples = s.num_samples;
  num_sets = s.num_sets;
  samples = s.samples;
  shuffled_indices = s.shuffled_indices;
  disk_samples = s.disk_samples;
  hemisphere_samples = s.hemisphere_samples;
  sphere_samples = s.sphere_samples;
  count	= s.count;
  jump = s.jump;
	
  return (*this);
}

void Sampler::set_nb_sets(const int np)
{
  num_sets = np;
}

const int Sampler::get_nb_samples() const
{
  return (num_samples);
}

void Sampler::shuffle_x()
{
  for (int p = 0; p < num_sets; p++)
    for (int i = 0; i <  num_samples - 1; i++)
    {
      int target = rand() % num_samples + p * num_samples;
      float temp = samples[i + p * num_samples + 1].x;
      samples[i + p * num_samples + 1].x = samples[target].x;
      samples[target].x = temp;
    }
}

void Sampler::shuffle_y()
{
  for (int p = 0; p < num_sets; p++)
    for (int i = 0; i <  num_samples - 1; i++)
    {
      int target = rand() % num_samples + p * num_samples;
      float temp = samples[i + p * num_samples + 1].y;
      samples[i + p * num_samples + 1].y = samples[target].y;
      samples[target].y = temp;
    }	
}

void Sampler::setup_shuffled_indices()
{
  shuffled_indices.reserve(num_samples * num_sets);
  std::vector<int> indices;
	
  for (int j = 0; j < num_samples; j++)
    indices.push_back(j);
	
  for (int p = 0; p < num_sets; p++)
  { 
    std::random_shuffle(indices.begin(), indices.end());	
		
    for (int j = 0; j < num_samples; j++)
      shuffled_indices.push_back(indices[j]);
  }
}

void Sampler::map_samples_to_unit_disk()
{
  int size = samples.size();
  float r, phi;		// polar coordinates
  Vector<float> sp; 		// sample point on unit disk
	
  disk_samples.reserve(size);
		
  for (int j = 0; j < size; j++) {
    // map sample point to [-1, 1] X [-1,1]
		 	
    sp.x = 2.0 * samples[j].x - 1.0;	
    sp.y = 2.0 * samples[j].y - 1.0;
			
    if (sp.x > -sp.y)
    {			// sectors 1 and 2
      if (sp.x > sp.y)
      {		// sector 1
	r = sp.x;
	phi = sp.y / sp.x;
      }
      else
      {					// sector 2
	r = sp.y;
	phi = 2 - sp.x / sp.y;
      }
    }
    else
    {						// sectors 3 and 4
      if (sp.x < sp.y)
      {		// sector 3
	r = -sp.x;
	phi = 4 + sp.y / sp.x;
      }
      else
      {					// sector 4
	r = -sp.y;
	if (sp.y != 0.0)	// avoid division by zero at origin
	  phi = 6 - sp.x / sp.y;
	else
	  phi  = 0.0;
      }
    }
		
    phi *= M_PI / 4.0;
    
    disk_samples[j].x = r * cos(phi);
    disk_samples[j].y = r * sin(phi);
  }
	
  samples.erase(samples.begin(), samples.end());
}

void Sampler::map_samples_to_hemisphere(const float exp)
{
  int size = samples.size();
  hemisphere_samples.reserve(num_samples * num_sets);
		
  for (int j = 0; j < size; j++)
  {
    float cos_phi = cos(2.0 * M_PI * samples[j].x);
    float sin_phi = sin(2.0 * M_PI * samples[j].x);	
    float cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
    float sin_theta = sqrt (1.0 - cos_theta * cos_theta);
    float pu = sin_theta * cos_phi;
    float pv = sin_theta * sin_phi;
    float pw = cos_theta;

    hemisphere_samples.push_back(Vector<float>(pu, pv, pw)); 
  }
}

void Sampler::map_samples_to_sphere()
{
  float r1, r2;
  float x, y, z;
  float r, phi;
		
  sphere_samples.reserve(num_samples * num_sets);   
		
  for (int j = 0; j < num_samples * num_sets; j++)
  {
    r1 = samples[j].x;
    r2 = samples[j].y;
    z = 1.0 - 2.0 * r1;
    r = sqrt(1.0 - z * z);
    phi = M_PI * 2 * r2;
    x = r * cos(phi);
    y = r * sin(phi);

    sphere_samples.push_back(Vector<float>(x, y, z)); 
  }
}

Vector<float> Sampler::sample_unit_square()
{
  if (count % num_samples == 0)
    jump = (rand() % num_sets) * num_samples;

  return (samples[jump + shuffled_indices[jump + count++ % num_samples]]);  
}


Vector<float> Sampler::sample_unit_disk()
{
  if (count % num_samples == 0)
    jump = (rand() % num_sets) * num_samples;
	
  return (disk_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

Vector<float> Sampler::sample_hemisphere()
{
  if (count % num_samples == 0)
    jump = (rand() % num_sets) * num_samples;
		
  return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);		
}

Vector<float> Sampler::sample_sphere()
{
  if (count % num_samples == 0)
    jump = (rand() % num_sets) * num_samples;
		
  return (sphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);		
}

Vector<float> Sampler::sample_one_set()
{
  return(samples[count++ % num_samples]);  
}

float Sampler::rand_float()
{
  return (static_cast<float>(rand() * (1 / RAND_MAX)));
}
