#define __USE_MINGW_ANSI_STDIO 0  //stops a redefinition error clash with stdio.h

#include<iostream>
#include "glitter.hpp"
#include "GLFW/glfw3.h"
#include "Loader.hpp"
#include "SimpleModel.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "common_defines.hpp"

using namespace std;

const string shader_dir = EXPAND_MACRO(SHADERS);
const string texture_dir = EXPAND_MACRO(TEXTURES);
const string model_dir = EXPAND_MACRO(MODELS);

Camera mainCam;
GLfloat timeElapsed = 0.0f;

//Prints a description of a glfw related error
void glfwError(int error, const char *description);

//Sets the width and height of the glViewPort if window is reszied
void reshape(GLFWwindow *window, int width, int height);

//Handles key input events
void handleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods);

//Initializes all the settings, etc for the rest of the program
void initEngine();

int main(void) {

    GLFWwindow *window;

    glfwSetErrorCallback(glfwError);
    /*Initialize the library*/
    if (!glfwInit()) {
        /*Initialization failed*/
        return -1;
    }

    window = glfwCreateWindow(1280, 720, "GEngine - Gainz", NULL, NULL);

    if (!window) {
        /*Window creation failed*/
        glfwTerminate();
        return -1;
    }
    /*Make the window's context current*/
    glfwMakeContextCurrent(window);

    gladLoadGL();
    /*Sets the call back function for when window is resized*/
    glfwSetFramebufferSizeCallback(window, reshape);
    /*Sets the callback function for key input events*/
    glfwSetKeyCallback(window, handleKeyInput);

    glEnable(GL_DEPTH_TEST);

    vector<glm::vec4> rectVerts = {
            //Left-bottom triangle
            glm::vec4(-0.5, 0.5, 0, 1),
            glm::vec4(-0.5, -0.5, 0, 1),
            glm::vec4(.5, -0.5, 0, 1),
            //Right-top triangle
            glm::vec4(0.5, -0.5, 0, 1),
            glm::vec4(0.5, 0.5, 0, 1),
            glm::vec4(-0.5, 0.5, 0, 1)
    };
    vector<glm::vec4> normals;
    vector<GLuint> textures, indicies;
    vector<glm::vec2> textureUVs = {
            //Left-bottom triangle
            glm::vec2(0.0, 0.0),
            glm::vec2(0.0, 1.0),
            glm::vec2(1.0, 1.0),
            //Right-top triangle
            glm::vec2(1.0, 1.0),
            glm::vec2(1.0, 0.0),
            glm::vec2(0.0, 0.0)
    };

    Loader loader;
    Shader shader(shader_dir + "v_shader.glsl", shader_dir + "f_shader.glsl");
    //SimpleModel rect(rectVerts, normals, textureUVs, indicies, textures, Material());
    CompositeModel comp;
    loader.loadModelFromFile(model_dir + "cube3.obj", comp);

    vector<SimpleModel> * sModels = comp.getModels();

    for(int i=0; i < sModels->size(); ++i){
        loader.loadToVao((*sModels)[i]);
    }
    //loader.loadToVao(rect);
    //rect.addTexture(loader.loadTexture("goku.jpg"));

    //loader.loadToVao(comp);

    Renderer renderer;

    GLfloat limitFPS = 1.0/60.0;
    GLfloat last = glfwGetTime();
    /*Loop while the window hasn't been close*/
    while (!glfwWindowShouldClose(window)) {
        GLfloat now = glfwGetTime();
        timeElapsed = (now - last)/limitFPS;
        last = glfwGetTime();

        renderer.prepare();
        shader.startShader();

        glm::mat4 modelM = glm::mat4(1.0f);
        glm::vec3 axis_of_rotation = glm::vec3(1.0f, 1.0f, 0.0f);
        modelM = glm::rotate(modelM, glm::radians(180.0f) * (GLfloat) glfwGetTime(), axis_of_rotation);
        glm::mat4 model_view = mainCam.modelViewMatrix();
        glm::mat4 perspective = mainCam.projectionMatrix();

        model_view *= modelM;

        shader.setUniformMatrix4fv("model_view", model_view);
        shader.setUniformMatrix4fv("perspective", perspective);

        //renderer.render(rect, shader);
        for(int i=0; i < sModels->size(); ++i){
           renderer.render((*sModels)[i], shader);
        }

        shader.stopShader();

        /*Swap front and back buffers after rendering to back for seamless image*/
        glfwSwapBuffers(window);
        /*Poll for and process events */
        glfwPollEvents();
    }

    loader.cleanUp();
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}

void glfwError(int error, const char *description) {
    fprintf(stderr, "Error: %s\n", description);
}

void reshape(GLFWwindow *window, int width, int height) {
    glViewport(0, 0, width, height);
}

void handleKeyInput(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(window, GLFW_TRUE);
    }
    else if(key == GLFW_KEY_W && action == GLFW_REPEAT){
        glm::vec3 newPosition = mainCam.getPosition() + (mainCam.getForward() * 5.0f * timeElapsed);
        mainCam.setPosition(newPosition);
    }
    else if(key == GLFW_KEY_S && action == GLFW_REPEAT){
        glm::vec3 newPosition = mainCam.getPosition() + ( -1.0f * mainCam.getForward() * 5.0f * timeElapsed);
        mainCam.setPosition(newPosition);
    }
    else if(key == GLFW_KEY_A && action == GLFW_REPEAT){
        glm::vec3 newPosition = mainCam.getPosition() + (-1.0f * mainCam.getRight() * 5.0f *  timeElapsed);
        mainCam.setPosition(newPosition);
    }
    else if(key == GLFW_KEY_D && action == GLFW_REPEAT){
        glm::vec3 newPosition = mainCam.getPosition() + (mainCam.getRight() * 5.0f * timeElapsed);
        mainCam.setPosition(newPosition);
    }
}

void initEngine() {

}

