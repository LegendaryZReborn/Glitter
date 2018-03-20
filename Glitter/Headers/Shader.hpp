#ifndef SHADER_H
#define SHADER_H
#include<glitter.hpp>
#include <GLFW/glfw3.h>
#include <string>
#include <fstream>
#include <iostream>
#include <common_defines.hpp>
using namespace std;

class Shader{
    public:
        Shader();
        Shader(string vertexShader, string fragmentShader);
        ~Shader();

        void startShader();
        void stopShader();
        GLuint getProgram();
        void setUniform1i(string identifier, GLint value);
        void setUniform1f(string identifier, GLfloat value);
        void setUniform3fv(string identifier, glm::vec3 value);
        void setUniform4fv(string identifier, glm::vec4 value);
        void setUniformMatrix4fv(string identifier, glm::mat4 value);

         void cleanUpShader();

    protected:
        GLuint programID;
        GLuint vertexShaderID;
        GLuint fragmentShaderID;

        GLuint loadShader(string sourceFileName, GLenum type);

};

#endif // SHADER_H
