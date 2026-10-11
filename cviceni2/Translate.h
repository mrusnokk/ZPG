/**
 * @file Translate.h
 * @brief Class representing a translation in 3D space.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Translate : public Transformation {
private:
    glm::vec3 position;
public:
    Translate(float x, float y, float z) : position(x, y, z) {}
    glm::mat4 getMatrix() override {
        return glm::translate(glm::mat4(1.0f), position);
    }
};
