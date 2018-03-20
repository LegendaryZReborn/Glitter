//
// Created by legen on 3/11/2018.
//

#include "Camera.hpp"

Camera::Camera(){
    position = glm::vec3(0.0f, 0.0f, -5.0f);
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::vec3(1.0f, 0.0f, 0.0f);
    forward = glm::vec3(0.0f, 0.0f, 1.0f);
    fov = 45.0f;
    aspect = 1280.0f/720.0f;
    nearPlane = 1.0f;
    farPlane = 20.0f;
}

Camera::Camera(glm::vec3 position, GLfloat fov, GLfloat aspect, GLfloat nearPlane, GLfloat farPlane){
    this->position = position;
    up = glm::vec3(0.0f, 1.0f, 0.0f);
    right = glm::vec3(1.0f, 0.0f, 0.0f);
    forward = glm::vec3(0.0f, 0.0f, 1.0f);
    fov = 45.0f;
    aspect = 1280.0f/720.0f;
    nearPlane = 1.0f;
    farPlane = 20.0f;
}

glm::vec3 Camera::getPosition() const{
    return position;
}

glm::vec3 Camera::getForward() const{
    return forward;
}

glm::vec3 Camera::getRight() const{
    return right;
}

glm::vec3 Camera::getUp() const{
    return up;
}

void Camera::setPosition(const glm::vec3 position){
    this->position = position;
}

void Camera::setFov(const GLfloat fov){
    this->fov = fov;
}

void Camera::setNearPlane(const GLfloat nearPlane){
    this->nearPlane = nearPlane;
}

void Camera::setFarPlane(const GLfloat farPlane){
    this->farPlane = farPlane;
}

void Camera::setAspect(const GLfloat width, const GLfloat height){
    aspect = width/height;
}

glm::mat4 Camera::modelViewMatrix() const{
    glm::mat4 matrix = glm::lookAt(position, position + forward, up);

    return matrix;
}

glm::mat4 Camera::projectionMatrix() const{
    glm::mat4 matrix = glm::perspective(glm::radians(fov), aspect, nearPlane, farPlane);

    return matrix;
}

Camera::~Camera(){

}