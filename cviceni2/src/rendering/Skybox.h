/**
 * @file Skybox.h
 * @brief Class representing a cubemap skybox rendered around the scene.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include <glad/gl.h>
#include <vector>
#include <string>
#include "rendering/Model.h"
#include "rendering/ShaderProgram.h"

class Skybox {
private:
    Model* model;
    ShaderProgram* shader;
    GLuint textureID;

    GLuint loadCubemap(const std::vector<std::string>& faces);

public:
    Skybox(const std::vector<std::string>& faces);
    ~Skybox();

    ShaderProgram* getShader() const;
    void draw();
};
