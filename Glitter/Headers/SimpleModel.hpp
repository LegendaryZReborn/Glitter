#ifndef SIMPLEMODEL_H
#define SIMPLEMODEL_H

#include<glitter.hpp>
#include<vector>
#include<common_structures.hpp>

class SimpleModel {
    friend class Loader;
    friend class Renderer;
public:
    SimpleModel();

    SimpleModel(std::vector<glm::vec4> vertices, std::vector<glm::vec4> normals,
    std::vector<glm::vec2> uVs, std::vector<GLuint> indicies, std::vector<GLuint> textures);

    ~SimpleModel();

    GLuint getVAO();

    void setVAO(const int val);

    GLuint getVBO();

    void setVBO(const int val);

    int getNumVertices();

    void setNumVertices(const int val);


private:
    std::vector<glm::vec4> vertices, normals;
    std::vector<glm::vec2> uVs;
    std::vector<GLuint> textures, indicies;

    GLuint vao, vbo;

    int numVertices;

};

#endif // SIMPLEMODEL_H
