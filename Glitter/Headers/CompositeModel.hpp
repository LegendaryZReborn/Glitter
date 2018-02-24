//
// Created by legen on 2/22/2018.
//

#ifndef GLITTER_COMPOSITEMODEL_HPP
#define GLITTER_COMPOSITEMODEL_HPP
#include "SimpleModel.hpp"
#include "Loader.hpp"
#include <vector>
#include <string>

class CompositeModel{
    friend class Renderer;
public:
    CompositeModel(std::string path, Loader& loader, Shader& shader);
    ~CompositeModel();
private:
    std::vector<SimpleModel> sModels;
    std::string directory;
};

#endif //GLITTER_COMPOSITEMODEL_HPP
