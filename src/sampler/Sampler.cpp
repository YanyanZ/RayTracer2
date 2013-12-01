#include <sampler/Sampler.cpp>

Sampler::Sampler::~Sampler()
{
}

Sampler::Sampler::Sampler()
  : num_samples (1), num_sets (83), count (0), jump (0)
{
  samples.reserve(num_samples * num_sets);
  setup_shuffled_indices();
}

Sampler::Sampler::Sampler(const int num)
  : num_samples (num), num_sets (83), count (0), jump (0)
{
  samples.reserve(num_samples * num_sets);
  setup_shuffled_indices();
}

Sampler::Sampler::Sampler(const int num, const int numsts)
  : num_samples (num), num_sets (numsts), count (0), jump (0)
{
  samples.reserve(num_samples * num_sets);
  setup_shuffled_indices();
}

Sampler::Sampler::Sampler(const Sampler& s)
 : num_samples(s.num_samples),
   num_sets(s.num_sets),
   samples(s.samples),
   shuffled_indices(s.shuffled_indices),
   disk_samples(s.disk_samples),
   hemisphere_samples(s.hemisphere_samples),
   sphere_samples(s.sphere_samples),
   count(s.count),
   jump(s.jump)
{
}

Sampler& Sampler::Sampler::operator=(const Sampler& s)
{
  num_samples = s.num_samples;
  num_sets = s.num_sets;
  samples = s.samples;
  shuffled_indices = s.shuffled_indices;
  disk_samples = s.disk_samples;
  hemisphere_samples = s.hemisphere_samples;
  sphere_samples = s.sphere_samples;
  count = s.count;
  jump = s.jump;

  return (*this);
}

void Sampler::Sampler::shuffle_x_coordinates()
{
  for (int p = 0; p < num_sets; p++)
    for (int i = 0; i < num_samples - 1; i++)
    {
      int target = rand() % num_samples + p * num_samples;
      float temp = samples[i + p * num_samples + 1].x;

      samples[i + p * num_samples + 1].x = samples[target].x;
      samples[target].x = temp;
    }
}

void Sampler::Sampler::shuffle_y_coordinates()
{
  for (int p = 0; p < num_sets; p++)
    for (int i = 0; i < num_samples - 1; i++)
    {
      int target = rand() % num_samples + p * num_samples;
      float temp = samples[i + p * num_samples + 1].y;

      samples[i + p * num_samples + 1].y = samples[target].y;
      samples[target].y = temp;
    }
}

void Sampler::Sampler::setup_shuffled_indices()
{
  shuffled_indices.resize(num_samples * num_sets);
  std::vector<int> indices;

  for (int j = 0; j < num_samples; j++)
    indices.push_back(j);

  for (int p = 0; p < num_sets; p++)
  {
    random_suffle(indices.begin(), indices.end());

    for (int j = 0; j < num_samples; j++)
      shuffled_indices.push_back(indices[j]);
  }
}

void Sampler::Sampler::map_samples_to_unit_disk()
{
  int size = samples.size();
  float r, phi; // Polar coordinates
  Vector<float> sp;

  disk_samples.resize(size);

  for (int j = 0; j < size; j++)
  {
    sp.x = 2 * samples[j].x - 1;
    sp.y = 2 * samples[j].y - 1;

    if (sp.x > -sp.y)
    {
      if (sp.x > sp.y)
      {
	r = sp.x;
	phi = sp.y / sp.x;
      }
      else
      {
	r = sp.y;
	phi = 2 - sp.x / sp.y;
      }
    }
    else
    {
      if (sp.x < sp.y)
      {
	r = -sp.y;
	phi = 4 + sp.y / sp.x;
      }
      else
      {
	r = -sp.y;
	if (sp.y != 0)
	  phi = 6 - sp.x / sp.y;
	else
	  phi = 0;
      }
    }
    phi *= M_PI / 4;

    disk_samples[j].x = r *cos(phi);
    disk_samples[j].y = r *sin(phi);
  }
  samples.erase(samples.begin(), samples.end());
}

void Sampler::Sampler::map_samples_to_hemisphere(const float exp)
{
  int size = samples.size();

  hemisphere_samples.resize(num_samples * num_sets);

  for (int j = 0; j < size; j++)
  {
    float cos_phi = cos(2.0 * M_PI * samples[j].x);
    float sin_phi = sin(2.0 * M_PI * samples[j].x);
    float cos_theta = pow((1.0 - samples[j].y), 1.0 / (exp + 1.0));
    float sin_theta = sqrt (1.0 - cos_theta * cos_theta);
    float pu = sin_theta * cos_phi;
    float pv = sin_theta * sin_phi;
    float pw = cos_theta;

    hemisphere_samples.push_back(Point3D(pu, pv, pw));
  }
}

void Sampler::Sampler::map_samples_to_sphere()
{
  float r1, r2;
  float x, y, z;
  float rm phi;

  sphere_samples.resize(num_samples * num_sets);

  for (int j = 0; j < num_samples * num_sets; j++)
  {
    r1 = samples[j].x;
    r2 = samples[j].y;
    z = 1 - 2 * r1;
    r = sqrt(1 - z * z);
    phi = M_PI * 2 * r2;
    x = r * cos(phi);
    y = r * sin(phi);

    sphere_samples.push_back(Vector<float>(x, y, z));
  }
}

Vector<float> Sampler::Sampler::sample_unit_square()
{
  if (count % num_samples == 0)
    jump = (rand() % num_sets) * num_samples;

  return (samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

Vector<float> Sampler::Sampler::sample_unit_disk()
{
  if (cout % num_samples == 0)
    jump = (rand() % num_sets) * num_samples;

  return (disk_samples[jump + shuffled_indices[jump +cout++ % num_samples]]);
}

Vector<float> Sampler::Sampler::sample_hemisphere()
{
  if (cout % num_samples == 0)
    jump = (rand() % num_sets) * num_samples;

  return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

Vector<float> Sampler::Sampler::sample_sphere()
{
  if (count % num_samples == 0)
    jump = (rand() % num_sets) * num_samples;

  return (sphere_samples[jump + shuffled_indices[jump + cout++ % num_samples]]);
}

Vecotr<float> Sampler::Sampler::sample_one_set()
{
  return (Samples[cout++ % num_samples]);
}
