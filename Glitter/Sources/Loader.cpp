#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>
#include "Loader.hpp"
#include <iostream>

Loader::Loader(){
}


void Loader::loadToVao(SimpleModel& model){
    float *data;
    vector<glm::vec4> vertices, normals;
    vector<glm::vec2> uVs;
    GLuint vaoID;

    vertices = model.vertices;
    normals = model.normals;
    uVs = model.uVs;

    vaoID = createVao();
    data = &vertices.data()->x;
    storeDataInVao(0, 4, data, vertices.size() * 4);
    data = &uVs.data()->x;
    storeDataInVao(1, 2, data, uVs.size() * 2);
    data = &normals.data()->x;
    storeDataInVao(2, 4, data, normals.size() * 4);
    glBindVertexArray(0);

    model.vao = vaoID;

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


GLuint Loader::loadTexture(string filename){
    string full_path = textures_dir + filename;
    GLint width, height, comp;
    unsigned char* image = stbi_load(full_path.c_str(), &width, &height, &comp, STBI_rgb_alpha);

    GLuint tex;
    if(image){

         //Output texture image data
        cout << "Loading Texture..." << endl;
        cout << full_path << endl;
        cout << "Dimensions: " << width << " by " << height << endl;
        cout << "Number of Components: " << comp << endl;
        
        glGenTextures(1, &tex);
        glActiveTexture(GL_TEXTURE0 + tex);
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

void Loader::loadModelFromFile(string path, CompositeModel& cModel) {
    Assimp::Importer importer;
    const aiScene* scene = importer.ReadFile(path, aiProcess_Triangulate | aiProcess_GenNormals
                                                   | aiProcess_FlipUVs);

    /*Check if the file was imported correctly into an aiScene*/
    if(!scene || scene->mFlags & AI_SCENE_FLAGS_INCOMPLETE || !scene->mRootNode)
    {
        cout << "ERROR: ASSIMP:: " << importer.GetErrorString() << endl;
        return;
    }

    cModel.directory = path.substr(0, path.find_last_of('/'));

    /*Take each of the scenes meshes and create a simple model with the meshes data
     * and add it to the vector sModels*/
    for(int i = 0; i < scene->mNumMeshes; ++i){
        aiMesh* mesh = scene->mMeshes[i];
        aiMaterial* material = nullptr;

        if(mesh->mMaterialIndex >=0)
            material = scene->mMaterials[mesh->mMaterialIndex];

        //Process mesh into a SimpleModel and add it to sModels
       cModel.sModels.push_back(processMesh(mesh, material));
    }
}

SimpleModel Loader::processMesh(aiMesh *mesh, aiMaterial* material){

    vector<glm::vec4> vertices, normals;
    vector<glm::vec2> uVs;
    vector<GLuint> textures, indicies;
    Material m;

    /*Get the vertices, normals and uvs*/
    for(int i = 0; i < mesh->mNumVertices; ++i){
        glm::vec4 v(mesh->mVertices[i].x, mesh->mVertices[i].y,
        mesh->mVertices[i].z, 1.0);
        vertices.push_back(v);

        glm::vec4 n(mesh->mNormals[i].x, mesh->mNormals[i].y,
                    mesh->mNormals[i].z, 0.0);
        normals.push_back(n);

        if(mesh->mTextureCoords[0]){
            glm::vec2 u(mesh->mTextureCoords[0][i].x,
                        mesh->mTextureCoords[0][i].y);
            uVs.push_back(u);
        }
    }

    /*Get the indicies for each face*/
    for(int i = 0; i < mesh->mNumFaces; ++i){
        aiFace face = mesh->mFaces[i];

        for(int j = 0; j < face.mNumIndices; ++j){
            indicies.push_back(face.mIndices[i]);
        }
    }

    //If there are materials for this mesh
    if(material) {
        /*Get Material data*/
        aiColor4D aiColor;

        aiGetMaterialColor(material, AI_MATKEY_COLOR_AMBIENT, &aiColor);
        m.ambient = glm::vec3(aiColor.r, aiColor.g, aiColor.b);
        aiGetMaterialColor(material, AI_MATKEY_COLOR_DIFFUSE, &aiColor);
        m.diffuse = glm::vec3(aiColor.r, aiColor.g, aiColor.b);
        aiGetMaterialColor(material, AI_MATKEY_COLOR_SPECULAR, &aiColor);
        m.specular = glm::vec3(aiColor.r, aiColor.g, aiColor.b);
        aiGetMaterialColor(material, AI_MATKEY_COLOR_EMISSIVE, &aiColor);
        m.emission = glm::vec3(aiColor.r, aiColor.g, aiColor.b);
        aiGetMaterialFloat(material, AI_MATKEY_SHININESS, &m.shininess);

        /*Get Texture data */
        for(int i = 0; i < material->GetTextureCount(aiTextureType_DIFFUSE); ++i){
            aiString p;
            material->GetTexture(aiTextureType_DIFFUSE, i, &p);

            //clean the path for only the filename if necessary
            string filename = p.C_Str();
            filename = "/" + filename;
            size_t pos = filename.rfind('/');

            if(pos != string::npos)
                filename = filename.substr(pos + 1, filename.size() - pos + 1);

            cout << filename << endl;
            textures.push_back(loadTexture(filename));
        }
    }

    return SimpleModel(vertices, normals, uVs, indicies, textures, m);
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
