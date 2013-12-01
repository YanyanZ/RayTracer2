# include <RayTracer.hpp>

RayTracer::~RayTracer()
{
  if (spheres)
    delete spheres;
}

RayTracer::RayTracer(std::string _in, std::string _out)
  : in (_in), out (_out)
{
}

void RayTracer::build()
{
  pugi::xml_document doc;
  doc.load_file(in.c_str());

  spheres = new std::vector<Objects::Basic::Sphere>();
  triangles = new std::vector<Objects::Basic::Triangle>();

  width = doc.child("scene").attribute("x").as_int();
  heigh = doc.child("scene").attribute("y").as_int();

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
      spheres->push_back(Objects::Basic::Sphere(vec, r,	RGBColor<float>(255, 0, 0)));
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

      triangles->push_back(Objects::Basic::Triangle(ve0, ve1, ve2,
						    RGBColor<float>(0, 255, 0)));
    }
  }

  for (unsigned int i = 0; i < spheres->size(); i++)
  {
    std::cout << "[SPHERE] " << (*spheres)[i].center << std::endl;
  }

  for (unsigned int i = 0; i < triangles->size(); i++)
  {
    std::cout << "[TRIANGLE] " << (*triangles)[i].s0 << std::endl;
  }

}

void RayTracer::trace()
{
  Vector<float> dir(0, 0, -1);

  im.resize(width);

  for (int i = 0; i < width; i++)
  {
    im[i].resize(heigh);
    for (int j = 0; j < heigh; j++)
    {
      Objects::HitRecord rec;
      float tmax = 1000000.0f;
      Engine::Ray r(Vector<float>(i, j, 0), dir);


      for (unsigned int n = 0; n < triangles->size(); n++)
      {
	if ((*triangles)[n].hit(r, 0.00001f, tmax, 0, rec) == true)
	  im[i][j] = rec.color;
      }

      for (unsigned int n = 0; n < spheres->size(); n++)
      {
	if ((*spheres)[n].hit(r, 0.00001f, tmax, 0, rec) == true)
	  im[i][j] = rec.color;
      }
    }
  }
}

void RayTracer::save()
{
  Display::Image image(im);

  image.show("test");
}
