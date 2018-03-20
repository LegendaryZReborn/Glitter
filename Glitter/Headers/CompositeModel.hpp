//
// Created by legen on 2/22/2018.
//

#ifndef GLITTER_COMPOSITEMODEL_HPP
#define GLITTER_COMPOSITEMODEL_HPP
#include "SimpleModel.hpp"
#include <vector>
#include <string>

class CompositeModel{
    friend class Renderer;
    friend class Loader;
public:
    CompositeModel(){
        directory = "";
    }
    std::vector<SimpleModel>* getModels(){
        return &sModels;
    }
    void draw(Shader& shader) const{
        for (auto m: sModels) {
            m.draw(shader);
        }
    }

    ~CompositeModel(){

    }
private:
    std::vector<SimpleModel> sModels;
    std::string directory;
};

#endif //GLITTER_COMPOSITEMODEL_HPP
