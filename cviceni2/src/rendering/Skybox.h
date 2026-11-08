#pragma once
#include <glad/gl.h>
#include <stb/stb_image.h>
#include <vector>
#include <string>
#include <iostream>

#include "textures/skybox.h"
#include "rendering/Model.h"
#include "rendering/ShaderProgram.h"

class Skybox {
private:
    Model* model;
    ShaderProgram* shader;
    GLuint textureID;

    GLuint loadCubemap(const std::vector<std::string>& faces) {
        GLuint id;
        glGenTextures(1, &id);
        glBindTexture(GL_TEXTURE_CUBE_MAP, id);

        stbi_set_flip_vertically_on_load(false);

        for (unsigned int i = 0; i < faces.size(); i++) {
            int w, h, ch;
            unsigned char* data = stbi_load(faces[i].c_str(), &w, &h, &ch, 4);
            if (data) {
                glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i,
                    0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
                stbi_image_free(data);
            }
            else {
                std::cerr << "Chyba pri nacitani steny cubemapy: " << faces[i] << std::endl;
            }
        }

        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
        return id;
    }

public:
    Skybox(const std::vector<std::string>& faces) {
        model = new Model(skybox_vertices, sizeof(skybox_vertices), skybox_vertex_count, 3);
        shader = new ShaderProgram("shaders/skybox.vert", "shaders/skybox.frag");
        textureID = loadCubemap(faces);
    }

    ~Skybox() {
        delete model;
        delete shader;
        glDeleteTextures(1, &textureID);
    }

    ShaderProgram* getShader() const {
        return shader;
    }

    void draw() {
        shader->use();
        shader->setUniform("skybox", 0);

        glActiveTexture(GL_TEXTURE0);
        glBindTexture(GL_TEXTURE_CUBE_MAP, textureID);

        model->draw();

        glBindTexture(GL_TEXTURE_CUBE_MAP, 0);
    }
};