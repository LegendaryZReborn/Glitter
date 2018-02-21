#ifndef LOADER_H
#define LOADER_H
#include "SimpleModel.hpp"
#include "TexturedModel.hpp"
#include <glm/glm.hpp>
#include <vector>
#include <string>

using namespace std;

class Loader{
    public:
        Loader();
        ~Loader();

        //Load data to VAO for an untextured object
        SimpleModel loadToVao(vector<glm::vec4> vertices);
        //Load data to VAO for an textured object
        TexturedModel loadToVao(vector<glm::vec4> vertices, vector<glm::vec2> textures, GLuint texID);
        //Load texture into texture unit
        GLuint loadTexture(string filename, GLuint unit);
        void cleanUp();

    protected:

    private:
       GLuint createVao();
       void storeDataInVao(GLuint attributeNum, int size, float * data, int dSize);

       vector<GLuint> vaos;
       vector<GLuint> vbos;
       vector<GLuint> textures;

};

#endif // LOADER_H
