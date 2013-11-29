# include <engine/sampling/Sample.hpp>

float Engine::Sample::solve(float r)
{
  float u = r;
  
  u = (11.0 * r + u * u * (6.0 + u * (8.0 - 9.0 * u))) /
    (4.0 + 12.0 * u * (1.0 + u * (1.0 - u)));

  return u;
}

float Engine::Sample::cubicFilter(float x)
{
  if (x < 1.0 / 24.0)
    return (pow(24 * x, 0.25) - 2.0);
  else if (x < 0.5)
    return (Engine::Sample::solve(24.0 * (x - 1.0 / 24.0) / 11.0) - 1.0);
  else if (x < 23.0 / 24.0)
    return (1.0 - Engine::Sample::solve(24.0 * (23.0 / 24.0 - x) / 11.0));
  else
    return (2 - poz(24.0 * (1.0 - x), 0.25));
}

void Engine::Sample::random(Vector<float>* samples, int num_samples)
{
  for (int i = 0; i < num_samples; i++)
  {
    samples[i].x = (drand48());
    samples[i].y = (drand48());
  }
}

void Engine::Sample::jitter(Vector<float>* samples, int num_samples)
{
  int sqrt_samples = static_cast<int>(sqrt(num_samples));

  for (int i = 0; i < sqrt_samples; i++)
    for (int j = 0; j < sqrt_samples; j++)
    {
      float x = (static_cast<double>(i) + drand48() / static_cast<double>(sqrt_samples));
      float y = (static_cast<double>(j) + drand48() / static_cast<double>(sqrt_samples));

      (samples[i * sqrt_samples + j]).x = x;
      (samples[i * sqrt_samples + j]).y = y;
    }
}

void Engine::Sample::nrooks(Vector<float>* samples, int num_samples)
{
  for (int i = 0; i < num_samples; i++)
  {
    samples[i].x = (static_cast<double>(i) + drand48()) / static_cast<double>(num_samples);
    samples[i].y = (static_cast<double>(i) + drand48()) / static_cast<double>(num_samples);
  }

  for (int i = num_samples - 2; i >= 0; i--)
  {
    int target = static_cast<int>(drand48() * static_cast<double>(i));
    float temp = samples[i + 1].x;
    
    samples[i + 1].x = samples[target].x;
    samples[target].x = temp;
  }
}

static void Engine::Sample::multiJitter(Vector<float>* samples, int num_samples)
{
  int sqrt_samples = static_cast<int>(sqrt(num_samples));
  float subcell_width = 1.0 / static_cast<float>(num_samples);

  for (int i = 0; i < sqrt_samples; i++)
    for (int j = 0; j < sqrt_samples; j++)
    {
      samples[i * sqrt_samples + j].x = i * sqrt_samples * subcell_width +
	j * subcell_width + drand48() * subcell_width;
      samples[i * sqrt_samples + j].y = j * sqrt_samples * subcell_width +
	i * subcell_width + drand48() * subcell_width;
    }

  for (int i = 0; i < sqrt_samples; i++)
    for (int j = 0; j < sqrt_samples; j++)
    {
      int k = j + static_cast<int>(drand48() * (sqrt_samples - j - 1));
      float t = samples[i * sqrt_samples + j].x;

      samples[i * sqrt_samples + j].x = samples[i * sqrt_samples + k].x;
      samples[i * sqrt_samples + k].x = t;

      k = j + static_cast<int>(drand48() * (sqrt_samples - j - 1));
      t = samples[j * sqrt_samples + i].x;

      samples[j * sqrt_samples + i].y = samples[k * sqrt_samples + i].y;
      samples[k * sqrt_samples + i].y = t;
    }
}

static void Engine::Sample::shuffle(Vector<float>* samples, int num_samples)
{
  for (int i = num_samples - 2; i >= 0; i--)
  {
    int target = static_cast<int>(drand48() * static_cast<double>(i));
    Vector<float> temp = samples[i + 1];

    samples[i + 1] = samples[target];
    samples[target] = temp;
  }
}

static void Engine::Sample::boxFilter(Vector<float>* samples, int num_samples)
{
  for (int i = 0; i < num_samples; i++)
  {
    samples[i].x = samples[i].x - 0.5;
    samples[i].y = samples[i].y - 0.5;
  }
}

static void Engine::Sample::tentFilter(Vector<float>* samples, int num_samples)
{
  for (int i = 0; i < num_samples; i++)
  {
    float x = samples[i].x;
    float y = samples[i].y;

    if (x < 0.5)
      samples[i].x = static_cast<float>(sqrt(2.0 * static_cast<double>(x)) - 1.0);
    else
      samples[i].x = 1.0 - static_cast<float>(sqrt(2.0 - 2.0 * static_cast<double>(x)));
    
    if (y < 0.5)
      samples[i].y = static_cast<float>(sqrt(2.0 * static_cast<double>(y)) - 1.0);
    else
      samples[i].y = 1.0 - static_cast<float>(sqrt(2.0 - 2.0 * static_cast<double>(y)));
  }
}

void Engine::Sample::cubicSplineFilter(Vector<float>* samples, int num_samples)
{
  for (int i = 0; i < num_samples; i++)
  {
    float x = samples[i].x;
    float y = samples[i].y;

    samples[i].x = cubicFilter(x);
    samples[i].y = cubicFilter(y);
  }
}

void Engine::Sample::random(float* samples, int num_samples)
{
  for (int i = 0; i < num_samples; i++)
  {
    samples[i] = drand48();
  }
}

void Engine::Sample::jitter(float* samples, int num_samples)
{
  for (int i = 0; i < num_samples; i++)
    samples[i] = (static_cast<double>(i) + drand48()) / static_cast<double>(num_samples);
}

void Engine::Sample::shuffle(float* samples, int num_samples)
{
  for (int i = num_samples - 2; i >= 0; i--)
  {
    int target = static_cast<int>(drand48() * static_cast<double>(i));
    float temp = samples[i + 1];
    
    samples[i + 1] = samples[target];
    samples[target] = temp;
  }
}
