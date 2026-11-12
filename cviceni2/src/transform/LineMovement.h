#pragma once
#include "transform/Transformation.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class LineMovement : public Transformation {
private:
    glm::vec3 pointA;
    glm::vec3 pointB;
    float t;
    float speed;
    int direction;
    double lastTime;

public:
    LineMovement(const glm::vec3& a, const glm::vec3& b, float speed = 0.5f)
        : pointA(a), pointB(b), t(0.0f), speed(speed), direction(1) {
        lastTime = glfwGetTime();
    }

    glm::vec3 getPosition() const {
        return pointA + t * (pointB - pointA);
    }

    void update() {
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

    glm::mat4 getMatrix() override {
        update();
        glm::vec3 currentPos = getPosition();
        return glm::translate(glm::mat4(1.0f), currentPos);
    }

    float getT() const { return t; }
    void setT(float newT) { t = newT; }
    glm::vec3 getPointA() const { return pointA; }
    glm::vec3 getPointB() const { return pointB; }
};
