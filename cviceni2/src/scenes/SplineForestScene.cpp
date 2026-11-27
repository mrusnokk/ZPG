#include "scenes/SplineForestScene.h"
#include "lighting/DirectionalLight.h"
#include "models/tree.h"
#include "models/bushes.h"
#include "models/tplain.h"
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cstdlib>
#include <cstdio>

SplineForestScene::SplineForestScene(int w, int h) {
    this->cam = new Camera(glm::vec3(0.0f, 4.0f, 10.0f), w, h);
    this->cam->setProjection(60.0f, w / static_cast<float>(h), 0.1f, 300.0f);

    std::vector<std::string> faces = {
        "src/textures/cubemap/posx.jpg",
        "src/textures/cubemap/negx.jpg",
        "src/textures/cubemap/posy.jpg",
        "src/textures/cubemap/negy.jpg",
        "src/textures/cubemap/posz.jpg",
        "src/textures/cubemap/negz.jpg"
    };
    this->setSkybox(new Skybox(faces));

    this->addLight(new DirectionalLight(0, glm::vec3(0.4f, -0.8f, -0.3f), glm::vec3(1.0f, 0.96f, 0.88f), 1.1f));
    this->getOrCreateFlashlight();

    ShaderProgram* groundShader = new ShaderProgram("Shaders/multiLightTexture.vert", "Shaders/multiLightTexture.frag");
    groundShader->use();
    groundShader->setUniform("uvScale", 64.0f);

    ShaderProgram* treeInstShader = new ShaderProgram("Shaders/multiLightInstanced.vert", "Shaders/multiLight.frag");
    treeInstShader->use();
    treeInstShader->setUniform("objectColor", 0.0f, 0.0f, 0.0f);

    ShaderProgram* bushInstShader = new ShaderProgram("Shaders/multiLightInstanced.vert", "Shaders/multiLight.frag");
    bushInstShader->use();
    bushInstShader->setUniform("objectColor", 92 / 255.0f, 169 / 255.0f, 4 / 255.0f);

    this->addShader(groundShader);
    this->addShader(treeInstShader);
    this->addShader(bushInstShader);

    Texture* grassTexture = new Texture("src/textures/grass.jpg");
    this->addTexture(grassTexture);

    Material* groundMat = new Material(glm::vec3(0.15f), glm::vec3(0.85f), glm::vec3(0.1f), 8.0f);
    Material* treeMat = new Material(glm::vec3(0.18f), glm::vec3(0.85f), glm::vec3(0.15f), 12.0f);
    Material* bushMat = new Material(glm::vec3(0.18f), glm::vec3(0.8f), glm::vec3(0.15f), 10.0f);

    this->addMaterial(groundMat);
    this->addMaterial(treeMat);
    this->addMaterial(bushMat);

    Model* groundModel = new Model(tplain, sizeof(tplain), 6, 8);
    Model* treeModel = new Model(tree, sizeof(tree), 92814, 6);
    Model* bushModel = new Model(bushes, sizeof(bushes), 8730, 6);

    this->addModel(groundModel);
    this->addModel(treeModel);
    this->addModel(bushModel);

    DrawableObject* ground = new DrawableObject(groundModel, groundShader, groundMat, grassTexture, 1);
    TransformComposite* groundTc = new TransformComposite();
    groundTc->addTransformation(new Translate(0.0f, -0.8f, 0.0f));
    groundTc->addTransformation(new Scale(120.0f, 1.0f, 120.0f));
    ground->setTransformation(groundTc);
    this->addObject(ground);

    srand(42);

    const int treeCount = 200;
    std::vector<glm::mat4> treeMatrices;
    treeMatrices.reserve(treeCount);
    while (static_cast<int>(treeMatrices.size()) < treeCount) {
        float rX = (rand() % 18000 - 9000) / 100.0f;
        float rZ = (rand() % 18000 - 9000) / 100.0f;
        if (rX > -12.0f && rX < 12.0f && rZ > -12.0f && rZ < 12.0f) continue;

        float rRot = static_cast<float>(rand() % 360);
        float rScale = (rand() % 18 + 10) / 100.0f;

        glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(rX, -0.8f, rZ));
        m = glm::rotate(m, glm::radians(rRot), glm::vec3(0.0f, 1.0f, 0.0f));
        m = glm::scale(m, glm::vec3(rScale));
        treeMatrices.push_back(m);
    }
    treeModel->setInstanceMatrices(treeMatrices);

    DrawableObject* instancedTrees = new DrawableObject(treeModel, treeInstShader, treeMat, 2);
    this->addObject(instancedTrees);

    const int bushCount = 5800;
    std::vector<glm::mat4> bushMatrices;
    bushMatrices.reserve(bushCount);
    while (static_cast<int>(bushMatrices.size()) < bushCount) {
        float rX = (rand() % 18000 - 9000) / 100.0f;
        float rZ = (rand() % 18000 - 9000) / 100.0f;
        if (rX > -10.0f && rX < 10.0f && rZ > -10.0f && rZ < 10.0f) continue;

        float rRot = static_cast<float>(rand() % 360);
        float rScale = (rand() % 55 + 15) / 100.0f;

        glm::mat4 m = glm::translate(glm::mat4(1.0f), glm::vec3(rX, -0.8f, rZ));
        m = glm::rotate(m, glm::radians(rRot), glm::vec3(0.0f, 1.0f, 0.0f));
        m = glm::scale(m, glm::vec3(rScale));
        bushMatrices.push_back(m);
    }
    bushModel->setInstanceMatrices(bushMatrices);

    DrawableObject* instancedBushes = new DrawableObject(bushModel, bushInstShader, bushMat, 3);
    this->addObject(instancedBushes);

    printf("SplineForestScene: %d trees (1 drawCall) + %d bushes (1 drawCall) = %d instances.\n",
        treeCount, bushCount, treeCount + bushCount);
}
