#include "scenes/TriangleScene.h"
#include "models/triangle.h"
#include "models/rus0130.h"

TriangleScene::TriangleScene(int w, int h) {
    this->cam = new Camera(glm::vec3(0.0f, 0.0f, 3.0f), w, h);
    this->cam->setProjection(60.0f, w / static_cast<float>(h), 0.1f, 100.0f);

    ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
    this->addShader(shader);

    Model* triangleModel = new Model(triangle, sizeof(triangle), 3);
    Model* loginModel = new Model(login_model, sizeof(login_model), 6996);
    this->addModel(triangleModel);
    this->addModel(loginModel);

    DrawableObject* triangleObj = new DrawableObject(triangleModel, shader);
    this->addObject(triangleObj);

    DrawableObject* mySignature = new DrawableObject(loginModel, shader);
    TransformComposite* sigTc = new TransformComposite();
    sigTc->addTransformation(new Translate(-0.8f, 0.8f, 0.0f));
    sigTc->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
    mySignature->setTransformation(sigTc);
    this->addObject(mySignature);
}
