/**
 * @file ForestNightScene.h
 * @brief Demonstration game scene representing a mystical forest at night with multi-type lighting, interactive item collection, and dynamic models.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */

#pragma once
#include "scenes/Scene.h"
#include "models/tree.h"
#include "models/bushes.h"
#include "models/sphere.h"
#include "models/rus0130.h"
#include "models/clock.h"
#include "models/gift.h"
#include "models/shrek.h"
#include "models/tplain.h"
#include "camera/Camera.h"
#include <cstdio>
#include <ctime>
#include <numbers>
#include <vector>
#include <string>
#include <GLFW/glfw3.h>

class ForestNightScene : public Scene {
private:
    ShaderProgram* clockShader;
    ShaderProgram* tShader;
    ShaderProgram* bShader;
    ShaderProgram* groundShader;
    ShaderProgram* shrekShader;
    ShaderProgram* giftShader;

    Translate* fireflyMoves[4];
    Translate* patrolMove;
    Rotate* patrolRot;
    PointLight* fireLight = nullptr;

    float speed = 0.5f;
    int collectedGifts = 0;
    const int totalGifts = 5;

public:
    ForestNightScene(int w, int h) {
        this->cam = new Camera(glm::vec3(0.0f, 1.2f, 5.0f));
        this->cam->setProjection(60.0f, w / static_cast<float>(h), 0.1f, 100.0f);

        std::vector<std::string> faces = {
            "src/textures/cubemap_night/posx.jpg",
            "src/textures/cubemap_night/negx.jpg",
            "src/textures/cubemap_night/posy.jpg",
            "src/textures/cubemap_night/negy.jpg",
            "src/textures/cubemap_night/posz.jpg",
            "src/textures/cubemap_night/negz.jpg"
        };
        this->setSkybox(new Skybox(faces));

        this->addLight(new DirectionalLight(0, glm::vec3(0.4f, -0.8f, -0.4f), glm::vec3(0.35f, 0.46f, 0.75f), 0.25f));

        this->getOrCreateFlashlight();

        fireLight = new PointLight(2, glm::vec3(0.0f, -0.4f, 2.5f), glm::vec3(1.0f, 0.55f, 0.15f), 3.2f);
        this->addLight(fireLight);

        this->addLight(new PointLight(3, glm::vec3(0.0f), glm::vec3(0.3f, 1.0f, 0.2f), 1.2f));
        this->addLight(new PointLight(4, glm::vec3(0.0f), glm::vec3(1.0f, 0.85f, 0.2f), 1.2f));
        this->addLight(new PointLight(5, glm::vec3(0.0f), glm::vec3(0.2f, 0.7f, 1.0f), 1.2f));
        this->addLight(new PointLight(6, glm::vec3(0.0f), glm::vec3(0.9f, 0.3f, 0.8f), 1.2f));

        ShaderProgram* shader = new ShaderProgram("Shaders/basic.vert", "Shaders/basic.frag");
        ShaderProgram* fireflyShaders[4] = {
            new ShaderProgram("Shaders/basic.vert", "Shaders/lightGreen.frag"),
            new ShaderProgram("Shaders/basic.vert", "Shaders/lightYellow.frag"),
            new ShaderProgram("Shaders/basic.vert", "Shaders/lightBlue.frag"),
            new ShaderProgram("Shaders/basic.vert", "Shaders/lightRed.frag")
        };
        tShader = new ShaderProgram("Shaders/multiLight.vert", "Shaders/multiLight.frag");
        tShader->use();
        tShader->setUniform("objectColor", 0.0f, 0.0f, 0.0f);

        bShader = new ShaderProgram("Shaders/multiLight.vert", "Shaders/multiLight.frag");
        bShader->use();
        bShader->setUniform("objectColor", 92 / 255.0f, 169 / 255.0f, 4 / 255.0f);

        groundShader = new ShaderProgram("Shaders/multiLightTexture.vert", "Shaders/multiLightTexture.frag");
        groundShader->use();
        groundShader->setUniform("uvScale", 16.0f);

        shrekShader = new ShaderProgram("Shaders/multiLightTexture.vert", "Shaders/multiLightTexture.frag");
        giftShader = new ShaderProgram("Shaders/multiLight.vert", "Shaders/multiLight.frag");
        giftShader->use();
        giftShader->setUniform("objectColor", 0.95f, 0.15f, 0.15f);

        clockShader = new ShaderProgram("Shaders/clockShader.vert", "Shaders/clockShader.frag");

        this->addShader(shader);
        for (int i = 0; i < 4; i++) {
            this->addShader(fireflyShaders[i]);
        }
        this->addShader(tShader);
        this->addShader(bShader);
        this->addShader(groundShader);
        this->addShader(shrekShader);
        this->addShader(giftShader);
        this->addShader(clockShader);

        Texture* grassTexture = new Texture("src/textures/grass.jpg");
        Texture* shrekTexture = new Texture("src/textures/shrek.png");
        this->addTexture(grassTexture);
        this->addTexture(shrekTexture);

        Model* groundModel = new Model(tplain, sizeof(tplain), 6, 8);
        Model* treeModel = new Model(tree, sizeof(tree), 92814, 6);
        Model* bushModel = new Model(bushes, sizeof(bushes), 8730, 6);
        Model* sunModel = new Model(sphere, sizeof(sphere), 2880, 6);
        Model* login = new Model(login_model, sizeof(login_model), 6996, 6);
        Model* clModel = new Model(clockModel, sizeof(clockModel), 44826, 9);
        Model* giftModel = new Model(gift, sizeof(gift), 66624, 6);
        Model* shrekModel = new Model(ShrekModel, sizeof(ShrekModel), ShrekVertexCount, 8);

        this->addModel(groundModel);
        this->addModel(treeModel);
        this->addModel(bushModel);
        this->addModel(sunModel);
        this->addModel(login);
        this->addModel(clModel);
        this->addModel(giftModel);
        this->addModel(shrekModel);

        Material* groundMat = new Material(glm::vec3(0.08f), glm::vec3(0.85f), glm::vec3(0.15f), 8.0f);
        Material* treeMat = new Material(glm::vec3(0.1f), glm::vec3(0.8f), glm::vec3(0.5f), 12.0f);
        Material* bushMat = new Material(glm::vec3(0.1f), glm::vec3(0.75f), glm::vec3(0.2f), 10.0f);
        Material* giftMat = new Material(glm::vec3(0.2f), glm::vec3(0.9f, 0.1f, 0.1f), glm::vec3(1.0f, 1.0f, 1.0f), 64.0f);
        Material* shrekMat = new Material(glm::vec3(0.12f), glm::vec3(0.85f), glm::vec3(0.3f), 16.0f);

        this->addMaterial(groundMat);
        this->addMaterial(treeMat);
        this->addMaterial(bushMat);
        this->addMaterial(giftMat);
        this->addMaterial(shrekMat);

        DrawableObject* ground = new DrawableObject(groundModel, groundShader, groundMat, grassTexture, 1);
        TransformComposite* groundTc = new TransformComposite();
        groundTc->addTransformation(new Translate(0.0f, -0.8f, 0.0f));
        groundTc->addTransformation(new Scale(25.0f, 1.0f, 25.0f));
        ground->setTransformation(groundTc);
        this->addObject(ground);

        srand(static_cast<unsigned int>(time(nullptr)));

        for (int i = 0; i < 90; i++) {
            DrawableObject* t = new DrawableObject(treeModel, tShader, treeMat, 10 + i);

            float rX = (rand() % 1200 - 600) / 100.0f;
            float rZ = (rand() % 1200 - 600) / 100.0f;
            if (rX > -2.0f && rX < 2.0f && rZ > 1.0f && rZ < 5.0f) {
                rX += (rX >= 0.0f) ? 3.0f : -3.0f;
            }
            float rRot = static_cast<float>(rand() % 360);
            float rScale = (rand() % 16 + 10) / 100.0f;

            TransformComposite* treeTc = new TransformComposite();
            treeTc->addTransformation(new Translate(rX, -0.8f, rZ));
            treeTc->addTransformation(new Rotate(rRot, 0.0f, 1.0f, 0.0f));
            treeTc->addTransformation(new Scale(rScale, rScale, rScale));
            
            t->setTransformation(treeTc);
            this->addObject(t);
        }

        for (int i = 0; i < 80; i++) {
            DrawableObject* b = new DrawableObject(bushModel, bShader, bushMat, 110 + i);

            float rX = (rand() % 1200 - 600) / 100.0f;
            float rZ = (rand() % 1200 - 600) / 100.0f;
            if (rX > -1.5f && rX < 1.5f && rZ > 1.5f && rZ < 4.5f) {
                rX += (rX >= 0.0f) ? 2.5f : -2.5f;
            }
            float rRot = static_cast<float>(rand() % 360);
            float rScale = (rand() % 60 + 15) / 100.0f;

            TransformComposite* bushTc = new TransformComposite();
            bushTc->addTransformation(new Translate(rX, -0.8f, rZ));
            bushTc->addTransformation(new Rotate(rRot, 0.0f, 1.0f, 0.0f));
            bushTc->addTransformation(new Scale(rScale, rScale, rScale));

            b->setTransformation(bushTc);
            this->addObject(b);
        }

        for (int i = 0; i < 4; i++) {
            fireflyMoves[i] = new Translate(0.0f, 0.0f, 0.0f);
            DrawableObject* firefly = new DrawableObject(sunModel, fireflyShaders[i], 190 + i);
            TransformComposite* fireflyTc = new TransformComposite();
            fireflyTc->addTransformation(fireflyMoves[i]);
            fireflyTc->addTransformation(new Scale(0.04f, 0.04f, 0.04f));
            firefly->setTransformation(fireflyTc);
            this->addObject(firefly);
        }

        DrawableObject* campfireVisual = new DrawableObject(sunModel, fireflyShaders[3], 194);
        TransformComposite* fireTc = new TransformComposite();
        fireTc->addTransformation(new Translate(0.0f, -0.65f, 2.5f));
        fireTc->addTransformation(new Scale(0.12f, 0.12f, 0.12f));
        campfireVisual->setTransformation(fireTc);
        this->addObject(campfireVisual);

        patrolMove = new Translate(0.0f, -0.8f, 0.0f);
        patrolRot = new Rotate(0.0f, 0.0f, 1.0f, 0.0f);
        DrawableObject* shrekObj = new DrawableObject(shrekModel, shrekShader, shrekMat, shrekTexture, 2);
        TransformComposite* shrekTc = new TransformComposite();
        shrekTc->addTransformation(patrolMove);
        shrekTc->addTransformation(patrolRot);
        shrekTc->addTransformation(new Rotate(90.0f, 1.0f, 0.0f, 0.0f));
        shrekTc->addTransformation(new Scale(0.55f, 0.55f, 0.55f));
        shrekObj->setTransformation(shrekTc);
        this->addObject(shrekObj);

        glm::vec3 giftPositions[5] = {
            glm::vec3(-2.8f, -0.69f, 1.5f),
            glm::vec3(3.2f, -0.69f, -1.5f),
            glm::vec3(1.4f, -0.69f, 5.2f),
            glm::vec3(-1.6f, -0.69f, 3.2f),
            glm::vec3(4.2f, -0.69f, 3.5f)
        };
        for (int i = 0; i < totalGifts; i++) {
            DrawableObject* g = new DrawableObject(giftModel, giftShader, giftMat, 3 + i);
            TransformComposite* gTc = new TransformComposite();
            gTc->addTransformation(new Translate(giftPositions[i].x, giftPositions[i].y, giftPositions[i].z));
            gTc->addTransformation(new Rotate(static_cast<float>(i * 45), 0.0f, 1.0f, 0.0f));
            gTc->addTransformation(new Scale(0.7f, 0.7f, 0.7f));
            g->setTransformation(gTc);
            this->addObject(g);
        }

        DrawableObject* mySignature = new DrawableObject(login, shader, 195);
        TransformComposite* loginTc = new TransformComposite();
        loginTc->addTransformation(new Translate(-0.8f, 0.8f, -1.0f));
        loginTc->addTransformation(new Scale(0.2f, 0.2f, 0.2f));
        mySignature->setTransformation(loginTc);
        this->addObject(mySignature);

        DrawableObject* clock = new DrawableObject(clModel, clockShader, 196);
        TransformComposite* clockTc = new TransformComposite();
        clockTc->addTransformation(new Rotate(180.0f, 0.0f, 1.0f, 0.0f));
        clockTc->addTransformation(new Translate(0.0f, 3.0f, 6.0f));
        clockTc->addTransformation(new Scale(-1.5f, 1.5f, 1.5f));
        clock->setTransformation(clockTc);
        this->addObject(clock);

        DrawableObject* clock2 = new DrawableObject(clModel, clockShader, 197);
        TransformComposite* clockTc2 = new TransformComposite();
        clockTc2->addTransformation(new Translate(0.0f, 3.0f, 6.0f));
        clockTc2->addTransformation(new Scale(-1.5f, 1.5f, 1.5f));
        clock2->setTransformation(clockTc2);
        this->addObject(clock2);
    }

    void onObjectClick(int id) override {
        if (id >= 3 && id <= 7) {
            if (this->removeObject(id)) {
                collectedGifts++;
                printf(">>> DAREK SEBRAN! (Sebrano: %d / %d) <<<\n", collectedGifts, totalGifts);
                if (collectedGifts >= totalGifts) {
                    printf("*** GRATULACE! Nasel jsi vsech 5 darku v temnem lese!   ***\n");
                    printf("*** Skvela prace, nocni les byl uspesne prozkouman!     ***\n");
                }
            }
        }
    }

    void update() override {
        std::time_t t = std::time(nullptr);
        std::tm lt;
#if defined(_WIN32) || defined(_WIN64)
        localtime_s(&lt, &t);
#else
        localtime_r(&t, &lt);
#endif

        const float TWO_PI = std::numbers::pi * 2;
        float seconds = static_cast<float>(lt.tm_sec);
        float minutes = lt.tm_min + seconds / 60.0f;
        float hours = (lt.tm_hour % 12) + minutes / 60.0f;

        float currentTime = static_cast<float>(glfwGetTime());

        if (fireLight != nullptr) {
            float flicker = 3.0f + 0.5f * sin(currentTime * 13.0f) * cos(currentTime * 7.0f);
            fireLight->setIntensity(flicker);
        }

        if (patrolMove != nullptr && patrolRot != nullptr) {
            float patrolAngle = currentTime * 0.35f;
            float pX = sin(patrolAngle) * 3.8f;
            float pZ = cos(patrolAngle) * 3.8f + 1.0f;
            patrolMove->setPosition(pX, -0.8f, pZ);
            patrolRot->setAngle(glm::degrees(patrolAngle) + 90.0f);
        }

        glm::vec3 fireflyPos[4];
        fireflyPos[0] = glm::vec3(
            sin(currentTime * speed * 0.9f) * 3.2f,
            -0.2f + sin(currentTime * speed * 1.8f) * 0.4f,
            cos(currentTime * speed * 0.9f) * 3.2f
        );

        fireflyPos[1] = glm::vec3(
            cos(currentTime * speed * 0.7f + 1.5f) * 2.8f,
            0.0f + cos(currentTime * speed * 1.3f) * 0.5f,
            sin(currentTime * speed * 1.4f) * 3.0f
        );

        fireflyPos[2] = glm::vec3(
            sin(currentTime * speed * 1.1f + 3.0f) * 4.0f,
            -0.1f + sin(currentTime * speed * 0.8f) * 0.6f,
            cos(currentTime * speed * 0.6f + 2.0f) * 3.5f
        );

        fireflyPos[3] = glm::vec3(
            cos(-currentTime * speed * 0.8f + 4.5f) * 3.2f,
            0.1f + sin(currentTime * speed * 1.5f) * 0.4f,
            sin(-currentTime * speed * 0.8f + 4.5f) * 3.2f
        );

        for (int i = 0; i < 4; i++) {
            fireflyMoves[i]->setPosition(fireflyPos[i].x, fireflyPos[i].y, fireflyPos[i].z);
            int lightIdx = 3 + i;
            if (lightIdx < static_cast<int>(lights.size())) {
                lights[lightIdx]->setPosition(fireflyPos[i]);
            }
        }

        clockShader->use();
        clockShader->setUniform("secondAngle", -(seconds / 60.0f * TWO_PI));
        clockShader->setUniform("minuteAngle", -(minutes / 60.0f * TWO_PI));
        clockShader->setUniform("hourAngle", -(hours / 12.0f * TWO_PI));
    }
};
