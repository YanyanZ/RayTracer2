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

  //int x = doc.child("scene").attribute("x").as_int();
  //int y = doc.child("scene").attribute("y").as_int();

  spheres = new std::vector<Objects::Basic::Sphere>();

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
    }
  }
}

void RayTracer::trace()
{
}

void RayTracer::save()
{
}
