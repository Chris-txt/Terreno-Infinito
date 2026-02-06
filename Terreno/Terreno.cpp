#include "Terreno.h"

Terreno::Terreno(Camera* mainCamera, int gridX, int gridZ)
{
    this->gridX = gridX;
    this->gridZ = gridZ;
    this->cam = mainCamera;
    quadAttuale = glm::ivec2{
        floor(cam->Position.x / quadWidth),
        floor(cam->Position.z / quadWidth)
    };
    
    numIstanze = gridX * gridZ;
    translations = new glm::vec3[numIstanze];

    int index = 0;
    for (int z = -gridX / 2; z < gridZ / 2; ++z) {
        for (int x = -gridX / 2; x < gridZ / 2; ++x) {
            glm::vec3 translation(0.0f);
            translation.x = x * quadWidth;
            translation.z = z * quadWidth;
            translations[index++] = translation;
        }
    }
    glGenBuffers(1, &instanceVBO);
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(glm::vec3) * numIstanze, &translations[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    //quad vao, vbo, ebo
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &quadVBO);
    glGenBuffers(1, &EBO);
    //dati del quadrato
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // texture attributes
    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    //instance
    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(2);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glVertexAttribDivisor(2, 1);

    //texture
    int widthImg, heightImg, numColCh;
    stbi_set_flip_vertically_on_load(true);
    unsigned char* bytes = stbi_load("grass.jpg", &widthImg, &heightImg, &numColCh, 0);

    if (bytes == nullptr) {
        std::cout << "Failed to load texture 'grass.jpg': " << stbi_failure_reason() << std::endl;
    }

    glGenTextures(1, &texture);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);

    glBindTexture(GL_TEXTURE_2D, 0);
}

void Terreno::generaTerreno()
{
    //troviamo il quadrato dove siamo
    glm::ivec2 nuovoQuad = {
        glm::floor(cam->Position.x / quadWidth),
        glm::floor(cam->Position.z / quadWidth)
    };

    glm::ivec2 delta = nuovoQuad - quadAttuale;

    //stiamo nello stesso quadrato
    if (delta == glm::ivec2(0))
        return;

    quadAttuale = nuovoQuad;

    for (int i = 0; i < numIstanze; ++i) {

        glm::vec3& t = translations[i];

        // Spostamento lungo X
        if (delta.x != 0) {
            float gridSizeX = gridX * quadWidth;
            if (t.x < cam->Position.x - gridSizeX / 2)
                t.x += gridSizeX;
            else if (t.x > cam->Position.x + gridSizeX / 2)
                t.x -= gridSizeX;
        }

        // Spostamento lungo Z
        if (delta.y != 0) {
            float gridSizeZ = gridZ * quadWidth;
            if (t.z < cam->Position.z - gridSizeZ / 2)
                t.z += gridSizeZ;
            else if (t.z > cam->Position.z + gridSizeZ / 2)
                t.z -= gridSizeZ;
        }
    }

    glBindBuffer(GL_ARRAY_BUFFER, instanceVBO);
    //questo ci permette di cambiare dati in un buffer gia esistente
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(glm::vec3) * numIstanze, translations);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}

void Terreno::draw(GLuint shader)
{
    glUniform3f(glGetUniformLocation(shader, "camPos"), cam->Position.x, cam->Position.y, cam->Position.z);

    glUniform1i(glGetUniformLocation(shader, "tex0"), 0);
    glBindVertexArray(VAO);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, texture);

    // disegnare con intanceed richiede il numero di istanze
    glDrawElementsInstanced(GL_TRIANGLES, sizeof(indices) / sizeof(unsigned int), GL_UNSIGNED_INT, 0, numIstanze);
    glBindTexture(GL_TEXTURE_2D, 0);
}

void Terreno::Delete() {
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &quadVBO);
    glDeleteBuffers(1, &EBO);
    glDeleteBuffers(1, &instanceVBO);
    glDeleteTextures(1, &texture);
}

Terreno::~Terreno()
{
    if (translations != nullptr)
        delete[] translations;
}
