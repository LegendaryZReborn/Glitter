#ifndef LOADER_H
#define LOADER_H

#include "SimpleModel.hpp"
#include "CompositeModel.hpp"
#include "Shader.hpp"
#include "Material.hpp"
#include <glitter.hpp>
#include <vector>
#include <string>
#include "common_defines.hpp"

using namespace std;

const string textures_dir = EXPAND_MACRO(TEXTURES);

class Loader {
public:
    Loader();

    ~Loader();

    //Load data to VAO for a SimpleModel
    void loadToVao(SimpleModel &model);

    //Load model from file at path
    //Returns the meshes represented in the file, each as a SimpleModel in sModels
    void loadModelFromFile(string path, CompositeModel& cModel);

    //Load texture
    GLuint loadTexture(string filepath);

    void cleanUp();

private:
    /*Helper methods*/
    GLuint createVao();

    void storeDataInVao(GLuint attributeNum, int size, float *data, int dSize);

    ///Processes an aiMesh's data into a SimpleModel and returns it
    SimpleModel processMesh(aiMesh *mesh, aiMaterial* material);

    /*Member attributes*/
    vector<GLuint> vaos;
    vector<GLuint> vbos;
    vector<GLuint> textures;

};

#endif // LOADER_H
