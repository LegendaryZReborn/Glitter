#ifndef SIMPLEMODEL_H
#define SIMPLEMODEL_H

#include<glad/glad.h>
#include <GLFW/glfw3.h>

class SimpleModel{
    public:
        SimpleModel();
        SimpleModel(GLuint vaoID, int numVert);
        ~SimpleModel();

        int GetvaoID();
        void SetvaoID(int val);
        int GetnumVertices();
        void SetnumVertices(int val);

    protected:
        int vaoID;
        int numVertices;
};

#endif // SIMPLEMODEL_H
