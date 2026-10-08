/**
 * @file SphereScene.h
 * @brief Scene class rendering sphere object.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "Scene.h"
#include "Models/sphere.h"
#include "Models/rus0130.h"

class SphereScene : public Scene {
public:
    SphereScene() {
        ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
        this->addShader(shader);

        Model* sphereModel = new Model(sphere, sizeof(sphere), 17280);
        Model* loginModel = new Model(login_model, sizeof(login_model), 6996);
        this->addModel(sphereModel);
        this->addModel(loginModel);

        DrawableObject* sphereObj = new DrawableObject(sphereModel, shader);
        this->addObject(sphereObj);

        DrawableObject* mySignature = new DrawableObject(loginModel, shader);
        mySignature->setPosition(-0.8f, 0.8f, 0.0f);
        mySignature->setScale(0.1f, 0.1f, -1.0f);
        this->addObject(mySignature);
    }
};