#ifndef SIMPLEMODEL_H
#define SIMPLEMODEL_H

#include <glitter.hpp>
#include <vector>
#include "Material.hpp"
#include "Shader.hpp"
#include <sstream>

class SimpleModel {
    friend class Loader;
    friend class Renderer;
public:
    SimpleModel();

    SimpleModel(std::vector<glm::vec4> vertices, std::vector<glm::vec4> normals,
    std::vector<glm::vec2> uVs, std::vector<GLuint> indicies, std::vector<GLuint> textures, Material mat);

    ~SimpleModel();

    GLuint getVAO() const;

    void setVAO(const int val);

    GLuint getVBO() const;

    void setVBO(const int val);

    int getNumVertices() const;

    void setNumVertices(const int val);

    void addTexture(const GLuint val);

    void setTextureUnits(Shader& shader) const;

    void draw(Shader& shader) const;

private:
    std::vector<glm::vec4> vertices, normals;
    std::vector<glm::vec2> uVs;
    std::vector<GLuint> textures, indicies;

    GLuint vao, vbo;

    int numVertices;

    Material material;
};

#endif // SIMPLEMODEL_H
