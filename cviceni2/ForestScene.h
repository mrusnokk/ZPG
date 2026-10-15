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
#include "Camera.h"
#include <cstdio>
#include <ctime>

class ForestScene : public Scene {
public:
    ForestScene() {
        this->cam = new Camera(glm::vec3(0.0f, 1.0f, 5.0f));
        this->cam->setProjection(60.0f, 800.0f / 600.0f, 0.1f, 100.0f);

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

        srand(static_cast<unsigned int>(time(nullptr)));

        for (int i = 0; i < 11; i++) {
            DrawableObject* t = new DrawableObject(treeModel, shader);
            
            float rX = (rand() % 200 - 100) / 100.0f;
            float rZ = (rand() % 200 - 100) / 100.0f;
            
            float rRot = static_cast<float>(rand() % 360);
            float rScale = (rand() % 16 + 10) / 100.0f;

            TransformComposite* treeTc = new TransformComposite();
            treeTc->addTransformation(new Translate(rX, -0.8f, rZ));
            treeTc->addTransformation(new Rotate(rRot, 0.0f, 1.0f, 0.0f));
            treeTc->addTransformation(new Scale(rScale, rScale, rScale));

            t->setTransformation(treeTc);
            this->addObject(t);
        }

        for (int i = 0; i < 15; i++) {
            DrawableObject* b = new DrawableObject(bushModel, shader);
            
            float rX = (rand() % 200 - 100) / 100.0f;
            float rZ = (rand() % 200 - 100) / 100.0f;
            float rRot = static_cast<float>(rand() % 360);
            float rScale = (rand() % 70 + 10) / 100.0f;

            TransformComposite* bushTc = new TransformComposite();

            bushTc->addTransformation(new Translate(rX, -0.8f, rZ));
            bushTc->addTransformation(new Rotate(rRot, 0.0f, 1.0f, 0.0f));
            bushTc->addTransformation(new Scale(rScale, rScale, rScale));

            b->setTransformation(bushTc);
            this->addObject(b);
        }
        
        DrawableObject* sun = new DrawableObject(sunModel, shaderSun);
        TransformComposite* sunTc = new TransformComposite();

        sunTc->addTransformation(new Translate(0.8f, 0.8f, 0.0f));
        sunTc->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
        sun->setTransformation(sunTc);

        this->addObject(sun);

        DrawableObject* mySignature = new DrawableObject(login, shader);
        TransformComposite* loginTc = new TransformComposite();

        loginTc->addTransformation(new Translate(-0.8f, 0.8f, -1.0f));
        loginTc->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
        mySignature->setTransformation(loginTc);

        this->addObject(mySignature);
    }
    void update() override{
        //cam->updateViewMatrix();
    }
};