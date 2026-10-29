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
    Scale(float x, float y, float z) : scaleVec(x, y, z) {}
    glm::mat4 getMatrix() override {
        return glm::scale(glm::mat4(1.0f), scaleVec);
    }
    void setScale(float x, float y, float z) 
    { 
        scaleVec = glm::vec3(x, y, z); 
    }
};