/**
 * @file CubicMovement.h
 * @brief Class representing movement along a single cubic Bezier curve with tangent-based orientation.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "transform/Transformation.h"
#include "transform/Translate.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class CubicMovement : public Transformation {
private:
    Translate* pointA;
    Translate* pointB;
    Translate* pointC;
    Translate* pointD;

    glm::mat4 A;
    float t;
    float speed;
    int direction;
    double lastTime;
    bool alignRotation;

public:
    CubicMovement(Translate* a, Translate* b, Translate* c, Translate* d, float speed = 0.5f, bool alignRotation = true);
    ~CubicMovement() override;

    glm::vec3 getPosition() const;
    glm::vec3 getTangent() const;
    void update();
    glm::mat4 getMatrix() override;
};
