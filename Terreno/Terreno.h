#ifndef TERRENO_CLASS_H
#define TERRENO_CLASS_H

#include <stb/stb_image.h>
#include "Shader.h"
#include "Camera.h"

static GLfloat vertices[] =
{ //     COORDINATES     /   TexCoord  //
    -5.0f, 0.0f,  5.0f,     0.0f, 1.0f, //in alto a sinistra
    -5.0f, 0.0f, -5.0f,     0.0f, 0.0f, //in basso a sinistra
     5.0f, 0.0f,  5.0f,     1.0f, 1.0f, //in alto a destra
     5.0f, 0.0f, -5.0f,     1.0f, 0.0f  //in basso a destra
};

static GLuint indices[] =
{
    0, 1, 2,
    1, 3, 2
};

class Terreno
{
private:
    Shader ourShader = Shader("default.vert", "default.frag");
    unsigned int quadVBO, VAO, EBO;
    unsigned int texture;
    int quadWidth = 10;
    Camera* cam = nullptr;
    glm::ivec2 quadAttuale;

    int GRID_X = 70;
    int GRID_Z = 70;
    int numIstanze = GRID_X * GRID_Z;

    unsigned int instanceVBO;
    glm::vec3* translations = nullptr;
public:
	Terreno(Camera* mainCamera);
    void generaTerreno();

    void draw();

    void Delete();
    ~Terreno();
};

#endif