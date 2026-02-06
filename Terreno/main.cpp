#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Mondo.h"
#include <iostream>
#include <Windows.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void processInput(GLFWwindow* window);

// settings
const unsigned int SCR_WIDTH = 900;
const unsigned int SCR_HEIGHT = 700;

int main()
{
    srand(time(NULL));

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    //crea la finestra
    GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Infinite Grass", NULL, NULL);
    if (window == NULL)
    {
        std::cout << "Failed to create GLFW window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

    //carica glad
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    //camera
    Camera camera(SCR_WIDTH, SCR_HEIGHT, glm::vec3(0.0f, 4.0f, -2.0f));

    //terreno
    Mondo mondo = Mondo(&camera);

    glEnable(GL_DEPTH_TEST);
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
    double previousTime = glfwGetTime();
    int frameCount = 0;
    //main loop
    while (!glfwWindowShouldClose(window))
    {
        double currentTime = glfwGetTime();
        frameCount++;

        if (currentTime - previousTime >= 1.0) {
            std::cout << "FPS: " << frameCount << "\n";
            frameCount = 0;
            previousTime = currentTime;
        }

        processInput(window);
        mondo.update();

        //render
        //colore nebbia = 0.902f, 0.871f, 0.945f
        //colore cielo chiaro = 0.0f, 0.6f, 0.9f
        //colore cielo normale = 0.529, 0.808, 0.922
        glm::vec3 skyColor = glm::vec3(0.902f, 0.871f, 0.945f);
        glClearColor(skyColor.r,skyColor.g,skyColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
        glUniform3f(glGetUniformLocation(mondo.getShader(), "fogColor"), skyColor.r,skyColor.g,skyColor.b);
        //camera update
        camera.Input(window);
        //aggiorna e esporta la matrice della camera al vertex shader
        camera.updateMatrix(50.0f, 0.1f, 500.0f);

        mondo.draw();

        //cambia i buffer
        glfwSwapBuffers(window);
        glfwPollEvents();

        //abbassa utilizzo della cpu
        Sleep(1);
    }

    //elimina le risorse che non servono più
    mondo.Delete();

    glfwTerminate();
    return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

void processInput(GLFWwindow* window)
{
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);
}