#include<iostream>
#include<glitter.hpp>
#include <GLFW/glfw3.h>
#include "Loader.hpp"
#include "SimpleModel.hpp"
#include "Renderer.hpp"
#include "Shader.hpp"

using namespace std;

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

    window = glfwCreateWindow(1280, 720, "I'm Back Bitches", NULL, NULL);

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
    Shader shader("Shaders/v_shader.glsl", "Shaders/f_shader.glsl");
    SimpleModel rect(rectVerts, normals, textureUVs, indicies, textures);

    loader.loadToVao(rect, shader);


    Renderer renderer;

    /*Loop while the window hasn't been close*/
    while (!glfwWindowShouldClose(window)) {
        renderer.prepare();
        renderer.render(rect, shader);
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
}

void initEngine() {

}

