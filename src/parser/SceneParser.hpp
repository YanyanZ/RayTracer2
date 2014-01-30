#ifndef SCENEPARSER_HPP
# define SCENEPARSER_HPP

# include "pugixml.hpp"
# include <string>
# include <vector>

# include <light/Ambiant.hpp>
# include <light/Point.hpp>

# include <tools/Transformer.hpp>

# include <scene/Scene.hpp>
# include <scene/Tracer.hpp>
# include <object/Sphere.hpp>
# include <object/Plan.hpp>
# include <object/Triangle.hpp>

class SceneParser
{
    public:
        SceneParser(std::string fn):
            s(nullptr),
            fileName(fn)
        {
        }

        SceneParser(void):
            s(nullptr),
            fileName("defaultFile.xml")
        {

        }

        Engine::Scene* getScene()
        {
            return s;
        }

        void parse(void);

    private:
        Engine::Scene* s;
        std::string fileName;
};

#endif // !SCENEPARSER_HPP
