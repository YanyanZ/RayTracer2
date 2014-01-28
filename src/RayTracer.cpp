# include <RayTracer.hpp>

RayTracer::~RayTracer()
{
  if (objects)
    delete objects;
  if (lights)
    delete lights;
}

RayTracer::RayTracer(std::string _in, std::string _out)
  : in (_in), out (_out)
{
}

void RayTracer::build()
{
  pugi::xml_document doc;
  doc.load_file(in.c_str());

  objects = new std::vector<Objects::Shape*>();
  lights = new std::vector<Light>();

  width = doc.child("scene").attribute("x").as_int();
  heigh = doc.child("scene").attribute("y").as_int();

  std::string name_sampler = doc.child("sampler").attribute("type").value();
  nb_samples = doc.child("sampler").attribute("nb_samples").as_int();
  std::cout << name_sampler << std::endl;

  if (name_sampler.compare("Jittered") == 0)
    sampler = new Jittered(nb_samples);

  pugi::xml_node first = doc.child("scene").child("objects");
  for (pugi::xml_node obj = first.child("object"); obj; obj = obj.next_sibling("object"))
  {
    std::string type(obj.attribute("type").value());
    if (type.compare("sphere") == 0)
    {
      int r = obj.attribute("radius").as_float();

      std::string tmp = obj.attribute("center").value();
      std::stringstream ss(tmp);
      std::vector<float> v;

      while (ss.good())
      {
	std::string substr;

	getline(ss, substr, ';');
	v.push_back(std::stof(substr));
      }

      Vector<float> vec = Vector<float>(v[0], v[1], v[2]);

      tmp = obj.attribute("center").value();
      std::stringstream ss2(tmp);
      v.clear();

      while (ss.good())
      {
	std::string substr;

	getline(ss2, substr, ';');
	v.push_back(std::stof(substr));
      }

      objects->push_back(new Objects::Basic::Sphere(vec, r, RGBColor<float>(v[0], v[1], v[2])));
    }

    type = obj.attribute("type").value();
    if (type.compare("triangle") == 0)
    {
      std::string tmp = obj.attribute("v0").value();
      std::stringstream ss(tmp);
      std::vector<float> v0;

      while (ss.good())
      {
	std::string substr;

	getline(ss, substr, ';');
	v0.push_back(std::stof(substr));
      }

      tmp = obj.attribute("v1").value();
      std::stringstream sss(tmp);
      std::vector<float> v1;

      while (sss.good())
      {
	std::string substr;

	getline(sss, substr, ';');
	v1.push_back(std::stof(substr));
      }

      tmp = obj.attribute("v2").value();
      std::stringstream ssss(tmp);
      std::vector<float> v2;

      while (ssss.good())
      {
	std::string substr;

	getline(ssss, substr, ';');
	v2.push_back(std::stof(substr));
      }

      Vector<float> ve0 = Vector<float>(v0[0], v0[1], v0[2]);
      Vector<float> ve1 = Vector<float>(v1[0], v1[1], v1[2]);
      Vector<float> ve2 = Vector<float>(v2[0], v2[1], v2[2]);

      objects->push_back(new Objects::Basic::Triangle(ve0, ve1, ve2,
						      RGBColor<float>(0, 255, 0)));
    }
  }

  first = doc.child("scene").child("lights");
  for (pugi::xml_node obj = first.child("light"); obj; obj = obj.next_sibling("light"))
  {
    std::string tmp = obj.attribute("dir").value();
    std::stringstream ssss(tmp);
    std::vector<float> v;

    while (ssss.good())
    {
      std::string substr;

      getline(ssss, substr, ';');
      v.push_back(std::stof(substr));
    }

    Vector<float> dir = Vector<float>(v[0], v[1], v[2]);

    tmp = obj.attribute("origin").value();
    std::stringstream sssss(tmp);
    std::vector<float> orig;

    while (sssss.good())
    {
      std::string substr;

      getline(sssss, substr, ';');
      orig.push_back(std::stof(substr));
    }

    Vector<float> o = Vector<float>(orig[0], orig[1], orig[2]);

    Light l = Light(RGBColor<float>(0,0,0), dir, o);

    lights->push_back(l);
  }

  //for (unsigned int i = 0; i < lights->size(); i++)
  //  std::cout << (*lights)[i] << std::endl;

  //if (sampler != NULL)
  //  std::cout << sampler->print() << std::endl;

  for (unsigned int i = 0; i < objects->size(); i++)
    std::cout << (*objects)[i]->print() << std::endl;
}

void RayTracer::trace()
{
  Vector<float> dir(0, 0, -1);
  int n = static_cast<int>(sqrt(2));
  //float psize = 1;
  Camera cam({0.2, 0, -0.1}, {0, 0, -1}, {0, 1, 0},
	     101, -2, 2, -2, 2, 2);

  im.resize(width);

  for (int i = 0; i < width; i++)
  {
    im[i].resize(heigh);
    for (int j = 0; j < heigh; j++)
    {
      for (int p = 0; p < n; p++)
	for (int q = 0; q < n; q++)
	{
	  Objects::HitRecord rec;
	  float tmax = 1000000.0f;
	  //Tools::Ray r(Vector<float>(psize * (i - 0.5 * width + (p + 0.5) / n),
	  //			     psize * (j - 0.5 * heigh + (q + 0.5) / n), 0), dir);
	  Tools::Ray r = cam.getRay(i, j, 0.1, 0.1);
	  //std::cout << r.origin() << " " << r.direction() << std::endl;
	  for (unsigned int n = 0; n < objects->size(); n++)
	  {
	    if ((*objects)[n]->hit(r, 0.00001f, tmax, 0, rec) == true)
	      im[i][j] =  rec.color;
	  }
	}

      im[i][j].r = im[i][j].r / 1;
      im[i][j].g = im[i][j].g / 1;
      im[i][j].b = im[i][j].b / 1;

      im[i][j] = im[i][j] * 1.0;
    }
  }
}

void RayTracer::save()
{
  Display::Image image(im);

  image.show("test");
}
