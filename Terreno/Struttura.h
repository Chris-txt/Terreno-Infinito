#ifndef STRUTTURA_CLASS_H
#define STRUTTURA_CLASS_H

#include "Shader.h"
#include <stb/stb_image.h>
#include <glm/glm.hpp>

static GLfloat structureVert[] = {
//     COORDINATES      /   TexCoord  //
    -10.0f,  0.0f,   10.0f,     0.0f, 0.0f, //0
    -10.0f,  0.0f,  -10.0f,     0.0f, 0.0f, //1
     10.0f,  0.0f,   10.0f,     1.0f, 0.0f, //2
     10.0f,	 0.0f,  -10.0f,     1.0f, 0.0f, //3

    -10.0f, 100.0f,  10.0f,    0.0f, 5.0f, //4
    -10.0f, 100.0f, -10.0f,    0.0f, 5.0f, //5
     10.0f, 100.0f,  10.0f,    1.0f, 5.0f, //6
     10.0f, 100.0f, -10.0f,    1.0f, 5.0f  //7
};

static GLuint structureInd[] =
{
	0, 1, 2,
	1, 3, 2,

	4, 6, 5,
	6, 7, 5,

	0, 2, 4,
	2, 6, 4,

	3, 1, 7,
	1, 5, 7,

	1, 0, 5,
	0, 4, 5,

	2, 3, 6,
	3, 7, 6
};

class Struttura
{
private:
	unsigned int VAO, VBO, EBO;
	unsigned int instanceVBO;
	int numIstanze = 500;

	glm::vec3* posizioni = nullptr;
public:
	Struttura();

	void update();
	void draw();
	void Delete();

	~Struttura();
};

#endif