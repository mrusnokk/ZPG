#include "transform/Translate.h"

Translate::Translate(float x, float y, float z) : position(x, y, z) {}

glm::mat4 Translate::getMatrix() {
    return glm::translate(glm::mat4(1.0f), position);
}

void Translate::setPosition(float x, float y, float z) {
    position = glm::vec3(x, y, z);
}

glm::vec3 Translate::getPosition() const {
    return position;
}
