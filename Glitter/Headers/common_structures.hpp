//
// Created by legen on 2/22/2018.
//

#ifndef GLITTER_COMMON_STRUCTURES_HPP
#define GLITTER_COMMON_STRUCTURES_HPP
#pragma once

#include<string>
#include<glitter.hpp>

struct Texture{
    std::string path;
    GLuint id;
};

struct Vertex{
    glm::vec4 position;
    glm::vec4 normal;
    glm::vec2 uV;
};
#endif //GLITTER_COMMON_STRUCTURES_HPP
