//
// Created by legen on 2/22/2018.
//
#include "CompositeModel.hpp"

CompositeModel::CompositeModel(std::string path, Loader& loader, Shader& shader){
    loader.loadModelFromFile(path, sModels);

    for(auto m: sModels)
        loader.loadToVao(m, shader);

    directory = path.substr(0, path.find_last_of('/'));
}
CompositeModel::~CompositeModel(){

}