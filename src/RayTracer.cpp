# include <RayTracer.hpp>

RayTracer::~RayTracer()
{
  if (spheres)
    delete spheres;
  if (triangles)
    delete triangles;
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

  spheres = new std::vector<Objects::Basic::Sphere>();
  triangles = new std::vector<Objects::Basic::Triangle>();
  lights = new std::vector<Light>();

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
      std::cout << substr << std::endl;

      orig.push_back(std::stof(substr));
    }

    Vector<float> o = Vector<float>(orig[0], orig[1], orig[2]);

    Light l = Light(RGBColor<float>(0,0,0), dir, o);

    lights->push_back(l);
  }

  for (unsigned int i = 0; i < lights->size(); i++)
  {
    std::cout << "[LIGHTS]" << std::endl;
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
  Camera cam = Camera(Vector<float>(0, 0, 2),
		      Vector<float>(0, 0, -2),
		      Vector<float>(0, 1, 0),
		      1,
		      -2, -2,
		      2, 2,
		      2);  // Test cam marche pas
  
  im.resize(width);

  for (int i = 0; i < width; i++)
  {
    im[i].resize(heigh);
    for (int j = 0; j < heigh; j++)
    {
      Objects::HitRecord rec;
      float tmax = 1000000.0f;
      Tools::Ray r(Vector<float>(i, j, 0), dir);

      for (unsigned int n = 0; n < triangles->size(); n++)
      {
	//Tools::Ray tmp = cam.getRay(i, j, 1, 1);
	if ((*triangles)[n].hit(r, 0.00001f, tmax, 0, rec) == true)
	  im[i][j] = rec.color;
      }

      for (unsigned int n = 0; n < spheres->size(); n++)
      {
	//Tools::Ray tmp = cam.getRay(i, j, 0.01, 0.01);
	if ((*spheres)[n].hit(r, 0.00001f, tmax, 0, rec) == true)
	  im[i][j] = rec.color;
      }
    }
  }

  // Lights IN DEBUG
  for (unsigned int i = 0; i < lights->size(); i++)
  {
      Objects::HitRecord rec;
      float tmax = 1000000.0f;
      Tools::Ray r((*lights)[i].origin, (*lights)[i].dir);
      int x = (*lights)[i].origin.x;
      int y = (*lights)[i].origin.y;
      int radius = 100;

      for (int a = 0; a <= radius; a++)
	for (int b = 0; b <= radius; b++)
	{
	  for (unsigned int n = 0; n < triangles->size(); n++)
	  {
	    //Tools::Ray tmp = cam.getRay(i, j, 1, 1);
	    if ((*triangles)[n].hit(r, 0.00001f, tmax, 0, rec) == true)
	    {
	      //im[a + x][b + y] = RGBColor<float>(255, 255, 255);
	    }
	  }
	  
	  for (unsigned int n = 0; n < spheres->size(); n++)
	  {
	    //Tools::Ray tmp = cam.getRay(i, j, 0.01, 0.01);
	    if ((*spheres)[n].hit(r, 0.00001f, tmax, 0, rec) == true)
	    {
	      std::cout << rec.t << std::endl;
	      //im[a + x][b + y] = RGBColor<float>(255, 255, 255);
	    }
	  }	  
	}
  }

  // Antialiasing
  for (int n = 0; n < 3; n++)
    for (int i = 1; i < width - 1; i++)
      for (int j = 1; j < heigh - 1; j++)
      {
	im[i][j] = im[i][j] + 
	  im[i + 1][j + 1] +
	  im[i - 1][j - 1] +
	  im[i + 1][j - 1] +
	  im[i - 1][j + 1] +
	  im[i + 1][j] +
	  im[i - 1][j] +
	  im[i][j - 1] +
	  im[i][j + 1];
	
	im[i][j].r = im[i][j].r / 9;
	im[i][j].g = im[i][j].g / 9;
	im[i][j].b = im[i][j].b / 9;
      }
}

void RayTracer::save()
{
  Display::Image image(im);

  image.show("test");
}
