/**
 * @file TriangleScene.h
 * @brief Scene class rendering triangle.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "Scene.h"
#include "Models/triangle.h"
#include "Models/rus0130.h"

class TriangleScene : public Scene {
public:
    TriangleScene() {
        ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
        this->addShader(shader);

        Model* triangleModel = new Model(triangle, sizeof(triangle), 3);
        Model* loginModel = new Model(login_model, sizeof(login_model), 6996);
        this->addModel(triangleModel);
        this->addModel(loginModel);

        DrawableObject* triangleObj = new DrawableObject(triangleModel, shader);
        this->addObject(triangleObj);

        DrawableObject* mySignature = new DrawableObject(loginModel, shader);
        mySignature->setPosition(-0.8f, 0.8f, 0.0f);
        mySignature->setScale(0.1f, 0.1f, -1.0f);
        this->addObject(mySignature);
    }
};