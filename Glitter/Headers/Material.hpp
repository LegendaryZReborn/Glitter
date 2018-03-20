//
// Created by legen on 3/10/2018.
//

#ifndef GLITTER_MATERIAL_HPP
#define GLITTER_MATERIAL_HPP
#include <glitter.hpp>
#include <Shader.hpp>

class Material{
public:
    GLfloat shininess;
    glm::vec3 ambient, diffuse, specular, emission;

    Material(){
    }

    Material(glm::vec3 a, glm::vec3 d, glm::vec3 s, glm::vec3 e, GLfloat shine){
        ambient = a;
        diffuse = d;
        specular = s;
        emission = e;
        shininess = shine;
    }

    void setMaterials(Shader& shader) const{
        shader.setUniform1f("material.shininess", shininess);
        shader.setUniform3fv("material.ambient", ambient);
        shader.setUniform3fv("material.diffuse", diffuse);
        shader.setUniform3fv("material.specular", specular);

    }
};
#endif //GLITTER_MATERIAL_HPP
