#include "transform/Scale.h"

Scale::Scale(float x, float y, float z) : scaleVec(x, y, z) {}

glm::mat4 Scale::getMatrix() {
    return glm::scale(glm::mat4(1.0f), scaleVec);
}

void Scale::setScale(float x, float y, float z) {
    scaleVec = glm::vec3(x, y, z);
}
