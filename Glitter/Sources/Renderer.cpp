#include "Renderer.hpp"

Renderer::Renderer(){
    //ctor
}

void Renderer::render(const SimpleModel& model, Shader& shader){
    shader.startShader();
    //Send uniform data to shader
    shader.setUniform1i("tex", model.textures[0]);
    shader.setUniform1f("time", (GLfloat) glfwGetTime());
    shader.setUniform1i("hasTexture", 1);
    /*Render*/
    glBindVertexArray(model.vao);
    glDrawArrays(GL_TRIANGLES, 0, model.numVertices);
    glBindVertexArray(0);
    shader.stopShader();
}

void Renderer::prepare(){
     /*Clear the buffer*/
    glClearColor(1.0, 0.0, 0.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
}

Renderer::~Renderer(){
    //dtor
}
