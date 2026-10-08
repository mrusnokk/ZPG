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

        Transformation* tPosun = new Transformation();
        tPosun->setPosition(0.4f, 0.0f, 0.0f);

        Transformation* tRotace = new Transformation();
        tRotace->setRotation(45.0f, 0.0f, 0.0f, 1.0f);

        //triangleObj->addTransformation(tPosun);
        //triangleObj->addTransformation(tRotace);

        triangleObj->addTransformation(tRotace);
        triangleObj->addTransformation(tPosun);


        this->addObject(triangleObj);

        DrawableObject* mySignature = new DrawableObject(loginModel, shader);

        Transformation* sigTransform = new Transformation();
        sigTransform->setPosition(-0.8f, 0.8f, 0.0f);
        sigTransform->setScale(0.1f, 0.1f, -1.0f);

        mySignature->addTransformation(sigTransform);

        this->addObject(mySignature);
    }

};