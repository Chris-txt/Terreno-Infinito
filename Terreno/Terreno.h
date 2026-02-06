#ifndef TERRENO_CLASS_H
#define TERRENO_CLASS_H

#include <stb/stb_image.h>
#include "Camera.h"

//un singolo pezzo del terreno da cui prenderemo riferimento per l'instancing
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

//classe che gestisce la pianura di erba infinita
class Terreno
{
private:
    unsigned int quadVBO, VAO, EBO;
    unsigned int texture;
    const int quadWidth = 10;
    Camera* cam = nullptr;
    glm::ivec2 quadAttuale;

    int gridX;
    int gridZ;
    int numIstanze;

    unsigned int instanceVBO;
    glm::vec3* translations = nullptr;
public:
	Terreno(Camera* mainCamera, int gridX, int gridZ);

    void generaTerreno();
    void draw(GLuint shader);
    void Delete();
    
    ~Terreno();
};

#endif