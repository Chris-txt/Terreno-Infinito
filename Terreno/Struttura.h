#ifndef STRUTTURA_CLASS_H
#define STRUTTURA_CLASS_H

#include "Shader.h"
#include <stb/stb_image.h>
#include <glm/glm.hpp>

//letteralmente la stessa cosa del terreno ma 20 volte più alto e 2 volte più largo
static GLfloat structureVert[] = {
//          COORDINATE     /    TexCoord  //
    //+Z
    -10.0f,  0.0f,   10.0f,     0.0f, 0.0f, //0
     10.0f,  0.0f,   10.0f,     1.0f, 0.0f, //1
    -10.0f, 200.0f,  10.0f,     0.0f, 7.0f, //2
     10.0f, 200.0f,  10.0f,     1.0f, 6.0f, //3

    //-Z
     10.0f,  0.0f,  -10.0f,     0.0f, 0.0f, //4
    -10.0f,  0.0f,  -10.0f,     1.0f, 0.0f, //5
     10.0f, 200.0f, -10.0f,     0.0f, 7.0f, //6
    -10.0f, 200.0f, -10.0f,     1.0f, 7.0f, //7

    //-X
    -10.0f,  0.0f,  -10.0f,     0.0f, 0.0f, //8
    -10.0f,  0.0f,   10.0f,     1.0f, 0.0f, //9
    -10.0f, 200.0f, -10.0f,     0.0f, 7.0f, //10
    -10.0f, 200.0f,  10.0f,     1.0f, 7.0f, //11

    //+X
     10.0f,  0.0f,   10.0f,     0.0f, 0.0f, //12
     10.0f,  0.0f,  -10.0f,     1.0f, 0.0f, //13
     10.0f, 200.0f,  10.0f,     0.0f, 7.0f, //14
     10.0f, 200.0f, -10.0f,     1.0f, 7.0f, //15

    //Y = 200
    -10.0f, 200.0f,  10.0f,     0.0f, 0.0f, //16
    -10.0f, 200.0f, -10.0f,     0.0f, 1.0f, //17
     10.0f, 200.0f,  10.0f,     1.0f, 0.0f, //18
     10.0f, 200.0f, -10.0f,     1.0f, 1.0f, //19

    //Y = 0
    -10.0f,   0.0f,  10.0f,     0.0f, 0.0f, //20
     10.0f,   0.0f,  10.0f,     1.0f, 0.0f, //21
    -10.0f,   0.0f, -10.0f,     0.0f, 1.0f, //22
     10.0f,   0.0f, -10.0f,     1.0f, 1.0f  //23
};

static GLuint structureInd[] =
{
    //fronte
    0, 1, 2,
    1, 3, 2,

    //retro
    4, 5, 6,
    5, 7, 6,

    //sinistra
    8, 9, 10,
    9, 11, 10,

    //destra
    12, 13, 14,
    13, 15, 14,

    //cima
    16, 17, 18,
    17, 19, 18,

    //fondo
    20, 21, 22,
    21, 23, 22
};

//classe responsabile per quei pilsatri di cemento che non fanno niente ma sono belli da vedere
//forse avrei dovuto chiamarla 'Strutture' con il plurale
class Struttura
{
private:
	unsigned int VAO, VBO, EBO;
	unsigned int instanceVBO;
	unsigned int texture;

	int numIstanze = 500;
	glm::vec3* posizioni = nullptr;
public:
	Struttura();

	void update();
	void draw(GLuint shader);
	void Delete();

	~Struttura();
};

#endif