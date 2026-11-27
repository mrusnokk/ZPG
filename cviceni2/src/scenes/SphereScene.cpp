#include "scenes/SphereScene.h"
#include "models/sphere.h"
#include "models/rus0130.h"

SphereScene::SphereScene() {
    ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
    this->addShader(shader);

    Model* sphereModel = new Model(sphere, sizeof(sphere), 2880);
    Model* loginModel = new Model(login_model, sizeof(login_model), 6996);
    this->addModel(sphereModel);
    this->addModel(loginModel);

    DrawableObject* sphereObj = new DrawableObject(sphereModel, shader);
    this->addObject(sphereObj);

    DrawableObject* mySignature = new DrawableObject(loginModel, shader);
    this->addObject(mySignature);
}
