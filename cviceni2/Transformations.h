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

class Rotate : public Transformation {
private:
    float angle;
    glm::vec3 axis;
public:
    Rotate(float angle, float x, float y, float z) : angle(angle), axis(x, y, z) {}
    glm::mat4 getMatrix() override {
        return glm::rotate(glm::mat4(1.0f), glm::radians(angle), axis);
    }
};

class Scale : public Transformation {
private:
    glm::vec3 scaleVec;
public:
    Scale(float x, float y, float z) : scaleVec(x, y, z) {}
    glm::mat4 getMatrix() override {
        return glm::scale(glm::mat4(1.0f), scaleVec);
    }
};