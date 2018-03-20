//
// Created by legen on 3/11/2018.
//

#ifndef GLITTER_CAMERA_HPP
#define GLITTER_CAMERA_HPP
#include "glitter.hpp"

class Camera {
public:
    Camera();
    Camera(glm::vec3 position, GLfloat fov, GLfloat aspect,
           GLfloat nearPlane, GLfloat farPlane);
    glm::vec3 getPosition() const;
    glm::vec3 getForward() const;
    glm::vec3 getRight() const;
    glm::vec3 getUp() const;
    void setPosition(const glm::vec3 position);
    void setFov(const GLfloat fov);
    void setNearPlane(const GLfloat nearPlane);
    void setFarPlane(const GLfloat farPlane);
    void setAspect(const GLfloat width, const GLfloat height);
    glm::mat4 modelViewMatrix() const;
    glm::mat4 projectionMatrix() const;

    ~Camera();
private:
    glm::vec3 position;
    glm::vec3 up;
    glm::vec3 right;
    glm::vec3 forward;
    GLfloat fov, nearPlane, farPlane, aspect;

};


#endif //GLITTER_CAMERA_HPP
