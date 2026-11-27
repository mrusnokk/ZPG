#include "transform/CubicMovement.h"
#include <cmath>

CubicMovement::CubicMovement(Translate* a, Translate* b, Translate* c, Translate* d, float speed, bool alignRotation)
    : pointA(a), pointB(b), pointC(c), pointD(d), t(0.0f), speed(speed), direction(1), alignRotation(alignRotation) {
    if (pointA) pointA->addRef();
    if (pointB) pointB->addRef();
    if (pointC) pointC->addRef();
    if (pointD) pointD->addRef();

    A = glm::mat4(
        glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
        glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
        glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
        glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)
    );
    lastTime = glfwGetTime();
}

CubicMovement::~CubicMovement() {
    if (pointA) pointA->release();
    if (pointB) pointB->release();
    if (pointC) pointC->release();
    if (pointD) pointD->release();
}

glm::vec3 CubicMovement::getPosition() const {
    glm::vec4 parameters(t * t * t, t * t, t, 1.0f);
    glm::mat4x3 B(pointA->getPosition(), pointB->getPosition(), pointC->getPosition(), pointD->getPosition());
    return parameters * A * glm::transpose(B);
}

glm::vec3 CubicMovement::getTangent() const {
    glm::vec4 dParameters(3.0f * t * t, 2.0f * t, 1.0f, 0.0f);
    glm::mat4x3 B(pointA->getPosition(), pointB->getPosition(), pointC->getPosition(), pointD->getPosition());
    return dParameters * A * glm::transpose(B);
}

void CubicMovement::update() {
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

glm::mat4 CubicMovement::getMatrix() {
    update();
    glm::vec3 currentPos = getPosition();
    glm::mat4 m = glm::translate(glm::mat4(1.0f), currentPos);
    if (alignRotation) {
        glm::vec3 tan = getTangent() * static_cast<float>(direction);
        if (glm::length(tan) > 0.0001f) {
            tan = glm::normalize(tan);
            float angle = glm::degrees(std::atan2(tan.x, tan.z));
            m = glm::rotate(m, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
        }
    }
    return m;
}
