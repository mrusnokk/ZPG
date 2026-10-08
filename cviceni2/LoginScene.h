/**
 * @file LoginScene.h
 * @brief Scene class dedicated to rendering and rotating user login signature.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "Scene.h"
#include "Transformation.h"
#include "Models/rus0130.h"

class LoginScene : public Scene {
public:
    LoginScene() {
        ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
        this->addShader(shader);

        Model* loginModel = new Model(login_model, sizeof(login_model), 6996);
        this->addModel(loginModel);

        DrawableObject* login = new DrawableObject(loginModel, shader);
        login->setScale(0.5f, 0.5f, -1.0f);
        login->setRotation(45.0f, 15.0f, 0.0f, 1.0f); 
        this->addObject(login);
    }
};