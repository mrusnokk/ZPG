#include "scenes/LoginScene.h"
#include "models/rus0130.h"

LoginScene::LoginScene() {
    ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
    this->addShader(shader);

    Model* loginModel = new Model(login_model, sizeof(login_model), 6996);
    this->addModel(loginModel);

    DrawableObject* login = new DrawableObject(loginModel, shader);
    this->addObject(login);
}
