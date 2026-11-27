#include "transform/LineMovement.h"

LineMovement::LineMovement(const glm::vec3& a, const glm::vec3& b, float speed)
    : pointA(a), pointB(b), t(0.0f), speed(speed), direction(1) {
    lastTime = glfwGetTime();
}

glm::vec3 LineMovement::getPosition() const {
    return pointA + t * (pointB - pointA);
}

void LineMovement::update() {
    double currentTime = glfwGetTime();
    if (lastTime > 0.0) {
        float dt = static_cast<float>(currentTime - lastTime);
        if (dt > 0.0f && dt < 0.1f) {
            t += direction * speed * dt;
            if (t >= 1.0f) {
                t = 1.0f;
                direction = -1;
            }
            else if (t <= 0.0f) {
                t = 0.0f;
                direction = 1;
            }
        }
    }
    lastTime = currentTime;
}

glm::mat4 LineMovement::getMatrix() {
    update();
    glm::vec3 currentPos = getPosition();
    return glm::translate(glm::mat4(1.0f), currentPos);
}

float LineMovement::getT() const { return t; }
void LineMovement::setT(float newT) { t = newT; }
glm::vec3 LineMovement::getPointA() const { return pointA; }
glm::vec3 LineMovement::getPointB() const { return pointB; }
