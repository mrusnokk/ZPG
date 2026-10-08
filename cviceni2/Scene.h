/**
 * @file Scene.h
 *
 * @brief Class for managing and rendering a collection of drawable objects.
 *
 * @author Michael Rusnok (rus0130)
 *
 * @year 2026
 **/

#pragma once
#include <vector>
#include "DrawableObject.h"
#include "Model.h"
#include "ShaderProgram.h"

class Scene {
private:
    std::vector<DrawableObject*> objects;
    std::vector<Model*> models;
    std::vector<ShaderProgram*> shaders;

public:
    Scene();
    virtual ~Scene();

    void addObject(DrawableObject* object);
    void addModel(Model* model);
    void addShader(ShaderProgram* shader);

    virtual void draw();
};