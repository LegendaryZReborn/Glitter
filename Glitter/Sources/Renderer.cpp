#include "Renderer.hpp"

Renderer::Renderer(){
    //ctor
}

void Renderer::render(const SimpleModel& model, Shader& shader){
    //Send uniform data to shader
    shader.setUniform1f("time", (GLfloat) glfwGetTime());
    shader.setUniform1i("hasTexture", 1);

    model.setTextureUnits(shader);
    model.draw(shader);

}

void Renderer::prepare(){
     /*Clear the buffer*/
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);}

Renderer::~Renderer(){
    //dtor
}
