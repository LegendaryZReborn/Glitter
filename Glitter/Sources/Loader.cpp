#include "Loader.hpp"
#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include <iostream>

Loader::Loader(){
}

SimpleModel Loader::loadToVao(vector<glm::vec4> vertices){
    float *data;

    GLuint vaoID = createVao();
    data = &vertices.data()->x;
    storeDataInVao(0, 4, data, vertices.size() * 4);
    glBindVertexArray(0);
    SimpleModel model(vaoID, vertices.size());

    return model;
}

TexturedModel Loader::loadToVao(vector<glm::vec4> vertices, vector<glm::vec2> textures, GLuint texID){
    float *data;

    GLuint vaoID = createVao();
    data = &vertices.data()->x;
    storeDataInVao(0, 4, data, vertices.size() * 4);
    data = &textures.data()->x;
    storeDataInVao(1, 2, data, textures.size() * 2);
    glBindVertexArray(0);

    TexturedModel model(vaoID, texID, vertices.size());

    return model;
}

GLuint Loader::createVao(){
    GLuint vaoID;

    glGenVertexArrays(1, &vaoID);
    glBindVertexArray(vaoID);
    vaos.push_back(vaoID);

    return vaoID;
}

void Loader::storeDataInVao(GLuint attributeNum, int size, float* data, int dSize){
    GLuint vboID;
    int dataSize = dSize * sizeof(float);

    glGenBuffers(1, &vboID);
    glBindBuffer(GL_ARRAY_BUFFER, vboID);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributeNum, size, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(attributeNum);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    vbos.push_back(vboID);
}


GLuint Loader::loadTexture(string filename, GLuint unit){
    string full_path = "textures\\" + filename + ".jpg";
    GLint width, height, comp;
    unsigned char* image = stbi_load(full_path.c_str(), &width, &height, &comp, STBI_rgb_alpha);

    GLuint tex;
    if(image){

         //Output texture image data
        cout << "Loading Texture..." << endl;
        cout << full_path << endl;
        cout << "Dimensions: " << width << " by " << height << endl;
        cout << "Number of Components: " << comp << endl;

        glActiveTexture(unit);
        glGenTextures(1, &tex);
        glBindTexture(GL_TEXTURE_2D, tex);

        //Load the texture image to the active texture unit
        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, image);

          //Apply settings
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
		glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

        stbi_image_free(image);
        textures.push_back(tex);

        return tex;
    }
    else{
	    cout << "Failed to load texture" << endl;
        return -1;
    }

}

void Loader::cleanUp(){
    for(auto vao: vaos)
    {
        glDeleteVertexArrays(1, &vao);
    }

    for(auto vbo: vbos)
    {
        glDeleteBuffers(1, &vbo);
    }

    for(auto tex: textures)
    {
        glDeleteTextures(1, &tex);
    }

}

Loader::~Loader(){
}
