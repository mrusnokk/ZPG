/**
 * @file ForestScene.h
 * @brief Scene class representing a forest with bushes and sun.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "Scene.h"
#include "Models/tree.h"
#include "Models/bushes.h"
#include "Models/sphere.h"
#include "Models/rus0130.h"
class ForestScene : public Scene {
public:
    ForestScene() {
        ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
        ShaderProgram* shaderSun = new ShaderProgram("Shaders/basic.vert", "Shaders/basic2.frag");
        Model* treeModel = new Model(tree, sizeof(tree), 92814);
        Model* bushModel = new Model(bushes, sizeof(bushes), 8730);
        Model* sunModel = new Model(sphere, sizeof(sphere), 17280);
        Model* login = new Model(login_model, sizeof(login_model), 6996);

        this->addShader(shader);
        this->addShader(shaderSun);
        this->addModel(treeModel);
        this->addModel(bushModel);
        this->addModel(sunModel);
        this->addModel(login);

        for (int i = 0; i < 12; i++) {
            DrawableObject* t = new DrawableObject(treeModel, shader);
            //t->setPosition(-1.0f + (i * 0.15f), -1.0f, 0.0f);
            //t->setScale(0.1f, 0.1f, 1.0f);
            this->addObject(t);
        }

        for (int i = 0; i < 12; i++) {
            DrawableObject* b = new DrawableObject(bushModel, shader);
            //b->setPosition(-0.9f + (i * 0.15f), -1.0f, 0.0f);
            //b->setScale(0.3f, 0.3f, 1.0f);
            this->addObject(b);
        }
        DrawableObject* sun = new DrawableObject(sunModel, shaderSun);
        //sun->setPosition(0.8f, 0.8f, 0.0f);
        //sun->setScale(0.1f,0.1f,1.0f);
        this->addObject(sun);
        DrawableObject* mySignature = new DrawableObject(login, shader);
        //mySignature->setPosition(-0.8f, 0.8f, 0.0f);
        //mySignature->setScale(0.1f, 0.1f, -1.0f);
        this->addObject(mySignature);
    }
};