#include "SimpleModel.hpp"

SimpleModel::SimpleModel(){

}

SimpleModel:: SimpleModel(std::vector<glm::vec4> vertices, std::vector<glm::vec4> normals,
                          std::vector<glm::vec2> uVs, std::vector<GLuint> indicies, std::vector<GLuint> textures, Material mat){

    this->vertices = vertices;
    this->normals = normals;
    this->uVs = uVs;
    this->textures = textures;
    this->indicies = indicies;;
    numVertices = vertices.size();
    this->material = mat;

}

GLuint SimpleModel::getVAO() const{
    return vao;
}

void SimpleModel::setVAO(const int val){
    vao = val;
}

GLuint SimpleModel::getVBO() const{
    return vbo;
}

void SimpleModel::setVBO(const int val){
    vbo = val;
}

int SimpleModel::getNumVertices() const{
    return numVertices;
}

void SimpleModel::setNumVertices(const int val){
     numVertices = val;
 }

void SimpleModel::addTexture(const GLuint val){
    textures.push_back(val);
}

void SimpleModel::setTextureUnits(Shader& shader) const{
    std::string sampName = "tex";
    stringstream str;
    std::string res;

    for(int i = 0; i < textures.size(); ++i){
        str << i;
        res = sampName + str.str();
        glActiveTexture(GL_TEXTURE0 + textures[i]);
        shader.setUniform1i(res, textures[i]);
    }
}

void SimpleModel::draw(Shader& shader) const{
    material.setMaterials(shader);
    glBindVertexArray(vao);
    glDrawArrays(GL_TRIANGLES, 0, numVertices);
    glBindVertexArray(0);
}
SimpleModel::~SimpleModel(){

}
