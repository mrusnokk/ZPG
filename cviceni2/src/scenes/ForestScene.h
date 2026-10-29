/**
 * @file ForestScene.h
 * @brief Scene class representing a forest with bushes and sun.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "scenes/Scene.h"
#include "models/tree.h"
#include "models/bushes.h"
#include "models/sphere.h"
#include "models/rus0130.h"
#include "models/plain.h"
#include "models/clock.h"
#include "camera/Camera.h"
#include <cstdio>
#include <ctime>
#include <numbers>
#include <GLFW/glfw3.h>

class ForestScene : public Scene {
private:
    ShaderProgram* clockShader;
    ShaderProgram* tShader;
    ShaderProgram* bShader;
    Translate* fireflyMove = new Translate(0.8f,0.8f,0.0f);
    float speed = 0.5f;

public:
    ForestScene(int w, int h) {
        this->cam = new Camera(glm::vec3(0.0f, 1.0f, 5.0f));
        this->cam->setProjection(60.0f, w / static_cast<float>(h), 0.1f, 100.0f);

		this->light = new Light(glm::vec3(0.8f, 0.8f, 0.0f), glm::vec3(195/255.0f, 223/255.0f, 224/255.0f), 1.0f);


        ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
        ShaderProgram* shaderSun = new ShaderProgram("Shaders/basic.vert", "Shaders/basic2.frag");
        tShader = new ShaderProgram("Shaders/utlumTreeShader.vert", "Shaders/utlumTreeShader.frag");
        bShader = new ShaderProgram("Shaders/utlumBushShader.vert", "Shaders/utlumBushShader.frag");
        clockShader = new ShaderProgram("Shaders/clockShader.vert", "Shaders/clockShader.frag");

        Model* treeModel = new Model(tree, sizeof(tree), 92814);
        Model* bushModel = new Model(bushes, sizeof(bushes), 8730);
        Model* sunModel = new Model(sphere, sizeof(sphere), 17280);
        Model* login = new Model(login_model, sizeof(login_model), 6996);
        Model* plainModel = new Model(plain, sizeof(plain), 6);
        Model* clModel = new Model(clockModel, sizeof(clockModel), 44826, 9);

        this->addShader(shader);
        this->addShader(shaderSun);
        this->addShader(tShader);
        this->addShader(bShader);
        this->addShader(clockShader);

        this->addModel(treeModel);
        this->addModel(bushModel);
        this->addModel(sunModel);
        this->addModel(login);
        this->addModel(plainModel);
        this->addModel(clModel);

        srand(static_cast<unsigned int>(time(nullptr)));

        for (int i = 0; i < 100; i++) {
            DrawableObject* t = new DrawableObject(treeModel, tShader);

            float rX = (rand() % 1000 - 500) / 100.0f;
            float rZ = (rand() % 1000 - 500) / 100.0f;
            float rRot = static_cast<float>(rand() % 360);
            float rScale = (rand() % 16 + 10) / 100.0f;

            TransformComposite* treeTc = new TransformComposite();
            treeTc->addTransformation(new Translate(rX, -0.8f, rZ));
            treeTc->addTransformation(new Rotate(rRot, 0.0f, 1.0f, 0.0f));
            treeTc->addTransformation(new Scale(rScale, rScale, rScale));

            t->setTransformation(treeTc);
            this->addObject(t);
        }

        for (int i = 0; i < 100; i++) {
            DrawableObject* b = new DrawableObject(bushModel, bShader);

            float rX = (rand() % 1000 - 500) / 100.0f;
            float rZ = (rand() % 1000 - 500) / 100.0f;
            float rRot = static_cast<float>(rand() % 360);
            float rScale = (rand() % 70 + 10) / 100.0f;

            TransformComposite* bushTc = new TransformComposite();
            bushTc->addTransformation(new Translate(rX, -0.8f, rZ));
            bushTc->addTransformation(new Rotate(rRot, 0.0f, 1.0f, 0.0f));
            bushTc->addTransformation(new Scale(rScale, rScale, rScale));

            b->setTransformation(bushTc);
            this->addObject(b);
        }

        DrawableObject* firefly = new DrawableObject(sunModel, shaderSun);
        TransformComposite* fireflyTc = new TransformComposite();
        fireflyTc->addTransformation(fireflyMove);
        fireflyTc->addTransformation(new Scale(0.008f, 0.008f, 0.008f));
        firefly->setTransformation(fireflyTc);
        this->addObject(firefly);

        DrawableObject* mySignature = new DrawableObject(login, shader);
        TransformComposite* loginTc = new TransformComposite();
        loginTc->addTransformation(new Translate(-0.8f, 0.8f, -1.0f));
        loginTc->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
        mySignature->setTransformation(loginTc);
        this->addObject(mySignature);

        DrawableObject* ground = new DrawableObject(plainModel, bShader);
        TransformComposite* groundTc = new TransformComposite();
        groundTc->addTransformation(new Translate(0.0f, -0.8f, 0.0f));
        groundTc->addTransformation(new Scale(10.0f, 1.0f, 10.0f));
        ground->setTransformation(groundTc);
        this->addObject(ground);

        DrawableObject* clock = new DrawableObject(clModel, clockShader);
        TransformComposite* clockTc = new TransformComposite();
        clockTc->addTransformation(new Rotate(180.0f, 0.0f, 1.0f, 0.0f));
        clockTc->addTransformation(new Translate(0.0f, 3.0f, 6.0f));
        clockTc->addTransformation(new Scale(-1.5f, 1.5f, 1.5f));
        clock->setTransformation(clockTc);
        this->addObject(clock);

        DrawableObject* clock2 = new DrawableObject(clModel, clockShader);
        TransformComposite* clockTc2 = new TransformComposite();
        clockTc2->addTransformation(new Translate(0.0f, 3.0f, 6.0f));
        clockTc2->addTransformation(new Scale(-1.5f, 1.5f, 1.5f));
        clock2->setTransformation(clockTc2);
        this->addObject(clock2);
    }

    void update() override {
        std::time_t t = std::time(nullptr);
        std::tm lt;
        localtime_s(&lt, &t);

        const float TWO_PI = std::numbers::pi * 2;
        float seconds = static_cast<float>(lt.tm_sec);
        float minutes = lt.tm_min + seconds / 60.0f;
        float hours = (lt.tm_hour % 12) + minutes / 60.0f;
        
        float currentTime = glfwGetTime();

        float fX = sin(currentTime * speed) * 3.0f;
        float fY = sin(currentTime * speed * 2.0f) * 0.5f;
        float fZ = cos(currentTime * speed) * 3.0f;
        
        fireflyMove->setPosition(fX,fY,fZ);
        
        tShader->use();
        tShader->setUniform("lightPosition", fX, fY, fZ);
        bShader->use();
        bShader->setUniform("lightPosition", fX, fY, fZ);

        clockShader->use();
        clockShader->setUniform("secondAngle", -(seconds / 60.0f * TWO_PI));
        clockShader->setUniform("minuteAngle", -(minutes / 60.0f * TWO_PI));
        clockShader->setUniform("hourAngle", -(hours / 12.0f * TWO_PI));

        

    }
};