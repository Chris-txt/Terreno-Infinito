#include "Camera.h"

Camera::Camera(int width, int height, glm::vec3 position)
{
	Camera::width = width;
	Camera::height = height;
	Position = position;
}

void Camera::updateMatrix(float FOVdeg, float nearPlane, float farPlane)
{
	// matrice per la vista
	glm::mat4 view = glm::mat4(1.0f);
	// matrice per la proiezione
	glm::mat4 proj = glm::mat4(1.0f);

	// la vista è uguale al punto in cui punta la camera
	view = glm::lookAt(Position, Position + Orientation, Up);
	// corregge l'aspect ratio usando divisione in virgola mobile
	proj = glm::perspective(glm::radians(FOVdeg), (float)width / (float)height, nearPlane, farPlane);
	// imposta la matrice della camera con la vista e la proiezione
	CameraMatrix = proj * view;
}

void Camera::Matrix(Shader& shader, const char* uniform)
{
	glUniformMatrix4fv(glGetUniformLocation(shader.ID, uniform), 1, GL_FALSE, glm::value_ptr(CameraMatrix));
}

void Camera::Input(GLFWwindow* window)
{
	//calcola deltaTime per movimento indipendente dal framerate
	float currentFrame = (float)glfwGetTime();
	deltaTime = currentFrame - lastFrame;
	lastFrame = currentFrame;

	//velocità effettiva con delta time
	float currentSpeed = speed;
	if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS) {
		currentSpeed *= sprintMultiplier;
	}
	float velocity = currentSpeed * deltaTime;

	// Direzione bloccando Y bloccata
	glm::vec3 orizzontale = Orientation;
	orizzontale.y = 0.0f;
	orizzontale = glm::normalize(orizzontale);
	glm::vec3 laterale = glm::normalize(glm::cross(orizzontale, Up));

	// input
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		Position += velocity * orizzontale;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		Position += velocity * -orizzontale;
	}
	if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
		Position += velocity * -laterale;
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		Position += velocity * laterale;
	}

	// input del mouse
	if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS)
	{
		//nasconde il cursore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

		//mantiene la camera dal saltare con il primo click
		if (firstClick)
		{
			glfwSetCursorPos(window, (width / 2), (height / 2));
			firstClick = false;
		}

		//tengono le coordinate del mouse
		double mouseX;
		double mouseY;
		//trova le coordinate del mouse
		glfwGetCursorPos(window, &mouseX, &mouseY);

		//Normalizza lo spostamento del cursore rispetto al centro, usa sensitivity come fattore
		float rotX = sensitivity * (float)(mouseY - (height / 2));
		float rotY = sensitivity * (float)(mouseX - (width / 2));

		//calcola i cambiamenti alla nuova rotazione
		glm::vec3 newOrientation = glm::rotate(Orientation, glm::radians(-rotX), glm::normalize(glm::cross(Orientation, Up)));

		//vede se la nuova orientazione è fattibile
		if (abs(glm::angle(newOrientation, Up) - glm::radians(90.0f)) <= glm::radians(85.0f))
		{
			Orientation = newOrientation;
		}

		//ruota l'orientazione a destra o a sinistra
		Orientation = glm::rotate(Orientation, glm::radians(-rotY), Up);

		//imposta il mouse al centro dello schermo così non rischia di uscire dalla finestra
		glfwSetCursorPos(window, (width / 2), (height / 2));
	}
	else if (glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE) {
		//mostra il cursore
		glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
		firstClick = true;
	}
}
