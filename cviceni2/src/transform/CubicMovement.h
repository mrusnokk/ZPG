#pragma once
#include "transform/Transformation.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>

class CubicMovement : public Transformation {
private:
    glm::vec3 pointA;
    glm::vec3 pointB;
    glm::vec3 pointC;
    glm::vec3 pointD;

    glm::mat4 A;
    glm::mat4x3 B;

    float t;
    float speed;
    int direction;
    double lastTime;

public:
    CubicMovement(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, float speed = 0.5f)
        : pointA(a), pointB(b), pointC(c), pointD(d), t(0.0f), speed(speed), direction(1) {
        A = glm::mat4(
            glm::vec4(-1.0f, 3.0f, -3.0f, 1.0f),
            glm::vec4(3.0f, -6.0f, 3.0f, 0.0f),
            glm::vec4(-3.0f, 3.0f, 0.0f, 0.0f),
            glm::vec4(1.0f, 0.0f, 0.0f, 0.0f)
        );
        B = glm::mat4x3(pointA, pointB, pointC, pointD);
        lastTime = glfwGetTime();
    }

    glm::vec3 getPosition() const {
        glm::vec4 parameters(t * t * t, t * t, t, 1.0f);
        return parameters * A * glm::transpose(B);
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
	glm::vec3 getPointC() const { return pointC; }
	glm::vec3 getPointD() const { return pointD; }
};
