#include "Mondo.h"

Mondo::Mondo(Camera* cam) : terreno(cam, GRID_X, GRID_Z) {
	this->cam = cam;
}

GLuint Mondo::getShader()
{
	return shader.ID;
}

void Mondo::update() {
	terreno.generaTerreno();
	struttura.update();
}

void Mondo::draw() {
	shader.Activate();
	cam->Matrix(shader, "camMatrix");
	
	terreno.draw(shader.ID);
	struttura.draw(shader.ID);
}

void Mondo::Delete() {
	terreno.Delete();
	struttura.Delete();
	shader.Delete();
}