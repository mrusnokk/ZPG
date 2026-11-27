/**
 * @file ForestScene.h
 * @brief Scene class representing a forest with bushes and sun.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "scenes/Scene.h"

class ForestScene : public Scene {
private:
    ShaderProgram* clockShader;
    ShaderProgram* tShader;
    ShaderProgram* bShader;

public:
    ForestScene(int w, int h);
    void update() override;
};
