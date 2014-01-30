#include "SceneParser.hpp"
#include <iostream>

using namespace pugi;

void SceneParser::parse(void)
{
    // if a scene already exists, delete it.
    if (s)
        delete s;

    s = new Engine::Scene();
    double max_trace_level = 3.0;
    int owidth = 1024;
    int oheight = 768;
    int anti = 1;
    double threshold = 0.3;
    int shadow = -1;
    int nbrays = 1;
    double cBG[3] = {0.2, 0.3, 0.5};


    double campos[4] = {0.2, 0.0, -0.1};
    double lookat[3] = {0, 0, 0};
    double fov = 130;

    xml_document doc;

    xml_parse_result result = doc.load_file(fileName.c_str());

    if (!result)
        std::cerr << "Parsing failed on file: " << fileName << std::endl;

    xml_node xmlScene = doc.child("scene");

    for (xml_node_iterator it = xmlScene.begin(); it != xmlScene.end(); ++it)
    {
        std::string name(it->name());

        if (name == "maxTraceLevel")
            max_trace_level = it->attribute("value").as_double();
        else if (name == "oWidth")
            owidth = it->attribute("value").as_int();
        else if (name == "oHeight")
            oheight = it->attribute("value").as_int();
        else if (name == "anti")
           anti = it->attribute("value").as_int();
        else if (name == "threshold")
           threshold = it->attribute("value").as_double();
        else if (name == "shadow")
            shadow = it->attribute("value").as_int();
        else if (name == "nbRays")
            nbrays = it->attribute("value").as_int();
        else if (name == "cBG")
        {
            cBG[0] = it->attribute("r").as_double();
            cBG[1] = it->attribute("g").as_double();
            cBG[2] = it->attribute("b").as_double();
        }
        else if (name == "camPos")
        {
            campos[0] = it->attribute("x").as_double();
            campos[1] = it->attribute("y").as_double();
            campos[2] = it->attribute("z").as_double();
        }
        else if (name == "lookAt")
        {
            lookat[0] = it->attribute("x").as_double();
            lookat[1] = it->attribute("y").as_double();
            lookat[2] = it->attribute("z").as_double();
        }
        else if (name == "fov")
            fov = it->attribute("value").as_double();

    }
    Engine::Camera* c = new Engine::Camera(campos, lookat);
    c->setTProjection(Engine::Camera::PERSPECTIVE);
    c->setSProjection(10);
    c->setFov(fov);
    s->changeCamera (c);

    s->setGlobalSetting(max_trace_level, anti, threshold, shadow,
            nbrays, oheight, owidth);
    s->setBackground(cBG);
}
