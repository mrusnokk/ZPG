#include "Transformation.h"
#include <glm/gtc/matrix_transform.hpp>

Transformation::Transformation() {
    position = glm::vec3(0.0f);
    scale = glm::vec3(1.0f);
    rotationAxis = glm::vec3(0.0f, 1.0f, 0.0f);
    rotationAngle = 0.0f;

    updateMatrix();
}

void Transformation::updateMatrix() {
    modelMatrix = glm::mat4(1.0f); 

    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::rotate(modelMatrix, glm::radians(rotationAngle), rotationAxis);
    modelMatrix = glm::scale(modelMatrix, scale);
}

void Transformation::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
    updateMatrix();
}

void Transformation::setScale(float x, float y, float z) {
    scale = glm::vec3(x, y, z);
    updateMatrix();
}

void Transformation::setRotation(float angle, float axisX, float axisY, float axisZ) {
    rotationAngle = angle;
    rotationAxis = glm::vec3(axisX, axisY, axisZ);
    updateMatrix();
}

glm::mat4 Transformation::getMatrix() {
    return modelMatrix;
}