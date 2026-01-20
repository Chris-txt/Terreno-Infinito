#include "Struttura.h"

Struttura::Struttura()
{   
    posizioni = new glm::vec3[numIstanze];
    int max = 600;
    int min = -600;
    for (int i = 0; i < numIstanze; ++i) {
        float x = (rand() % (max - min + 1)) + min;
        float z = (rand() % (max - min + 1)) + min;
        posizioni[i] = glm::vec3(x, (rand() % 80), z);
    }

    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * numIstanze, &posizioni[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //quad vao, vbo, ebo
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);
    glGenBuffers(1, &EBO);
    //dati del quadrato
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(structureVert), structureVert, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(structureInd), structureInd, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture attributes
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);
    //istanze
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);

}

void Struttura::update() {

}

void Struttura::draw() {
    glBindVertexArray(VAO);
    // disegnare con intanceed richiede il numero di istanze
    glDrawElementsInstanced(GL_TRIANGLES, sizeof(structureInd) / sizeof(unsigned int), GL_UNSIGNED_INT, 0, numIstanze);
}

void Struttura::Delete() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &instanceVBO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
}

Struttura::~Struttura()
{
    if (posizioni != nullptr)
        delete[] posizioni;
}
