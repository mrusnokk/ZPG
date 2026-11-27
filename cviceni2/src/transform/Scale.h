/**
 * @file Scale.h
 * @brief Class representing scaling of an object.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "transform/Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

class Scale : public Transformation {
private:
    glm::vec3 scaleVec;

public:
    Scale(float x, float y, float z);
    glm::mat4 getMatrix() override;
    void setScale(float x, float y, float z);
};
