#ifndef DRIVER_PARSER_HPP_
#define DRIVER_PARSER_HPP_
#include <istream>
#include <fstream>
#include <stdexcept>

#include "Scene.hpp"

namespace driver {

class ParsingError : public std::runtime_error
{
    public:
        ParsingError(const std::string &msg) : runtime_error(msg) {}
};

class SceneFileParser
{
    public:
        SceneFileParser(std::istream &is) : is_(is) {}
        simple_raytracer::Scene GetScene();

    private:
        std::istream &is_;
};

} // namespace driver

#endif //DRIVER_PARSER_HPP_
