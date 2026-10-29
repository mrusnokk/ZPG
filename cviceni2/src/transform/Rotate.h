/**
 * @file Rotate.h
 * @brief Class representing a rotation around a specific axis.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "transform/Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Rotate : public Transformation {
private:
    float angle;
    glm::vec3 axis;
public:
    Rotate(float angle, float x, float y, float z) : angle(angle), axis(x, y, z) {}
    glm::mat4 getMatrix() override {
        return glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    }
    void setAngle(float a) {
        this->angle = a;

    }
};