#include "SimpleModel.hpp"

SimpleModel::SimpleModel(){

}

SimpleModel:: SimpleModel(std::vector<glm::vec4> vertices, std::vector<glm::vec4> normals,
                          std::vector<glm::vec2> uVs, std::vector<GLuint> indicies, std::vector<GLuint> textures){

    this->vertices = vertices;
    this->normals = normals;
    this->uVs = uVs;
    this->textures = textures;
    this->indicies = indicies;;
    numVertices = vertices.size();
}

GLuint SimpleModel::getVAO(){
    return vao;
}

void SimpleModel::setVAO(const int val){
    vao = val;
}

GLuint SimpleModel::getVBO(){
    return vbo;
}

void SimpleModel::setVBO(const int val){
    vbo = val;
}

int SimpleModel::getNumVertices(){
    return numVertices;
}

void SimpleModel::setNumVertices(const int val){
     numVertices = val;
 }


SimpleModel::~SimpleModel(){

}
