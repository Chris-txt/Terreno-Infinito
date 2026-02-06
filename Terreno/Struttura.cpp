#include "Struttura.h"

Struttura::Struttura()
{   
    posizioni = new glm::vec3[numIstanze];
    int max = 600;
    int min = -600;
    for (int i = 0; i < numIstanze; ++i) {
        float x = (rand() % (max - min + 1)) + min;
        float z = (rand() % (max - min + 1)) + min;
        posizioni[i] = glm::vec3(x, (rand() % 60), z);
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

    //texture
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("concrete.jpg", &widthImg, &heightImg, &numColCh, 0);

    if (bytes == nullptr) {
        std::cout << "Failed to load texture 'concrete.jpg': " << stbi_failure_reason() << std::endl;
    }

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Struttura::update() {
    
}

void Struttura::draw(GLuint shader) {
    glUniform1i(glGetUniformLocation(shader, "tex0"), 1);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE1);
    glBindTexture(GL_TEXTURE_2D, texture);

    // disegnare con instanced richiede il numero di istanze
    glDrawElementsInstanced(GL_TRIANGLES, sizeof(structureInd) / sizeof(unsigned int), GL_UNSIGNED_INT, 0, numIstanze);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Struttura::Delete() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &instanceVBO);
    glDeleteBuffers(1, &VBO);
    glDeleteBuffers(1, &EBO);
    glDeleteTextures(1, &texture);
}

Struttura::~Struttura()
{
    if (posizioni != nullptr)
        delete[] posizioni;
}
