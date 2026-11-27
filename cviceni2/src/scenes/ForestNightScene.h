/**
 * @file ForestNightScene.h
 * @brief Demonstration game scene representing a mystical forest at night with multi-type lighting, interactive item collection, and dynamic models.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "scenes/Scene.h"
#include "lighting/PointLight.h"

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
    ForestNightScene(int w, int h);
    void onObjectClick(int id) override;
    void update() override;
};
