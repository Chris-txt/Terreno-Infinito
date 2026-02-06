#pragma once
#include "Terreno.h"
#include "Struttura.h"

//classe che contiene tutte le informazioni del mondo
class Mondo
{
private:
	int GRID_X = 80;
	int GRID_Z = 80;
	Shader shader = Shader("default.vert", "default.frag");

	Struttura struttura;
	Terreno terreno;
	Camera* cam = nullptr;
public:
	Mondo(Camera* cam);

	GLuint getShader();

	void draw();
	void update();
	void Delete();
};
