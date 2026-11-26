/**
 * @file CubicMovement.h
 * @brief Class representing movement along a single cubic Bezier curve with tangent-based orientation.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "transform/Transformation.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <cmath>

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
    bool alignRotation;
    float rotationOffset;

public:
    CubicMovement(const glm::vec3& a, const glm::vec3& b, const glm::vec3& c, const glm::vec3& d, float speed = 0.5f, bool alignRotation = true)
        : pointA(a), pointB(b), pointC(c), pointD(d), t(0.0f), speed(speed), direction(1), alignRotation(alignRotation), rotationOffset(0.0f) {
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

    glm::vec3 getTangent() const {
        glm::vec4 dParameters(3.0f * t * t, 2.0f * t, 1.0f, 0.0f);
        return dParameters * A * glm::transpose(B);
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
        glm::mat4 m = glm::translate(glm::mat4(1.0f), currentPos);
        if (alignRotation) {
            glm::vec3 tan = getTangent() * static_cast<float>(direction);
            if (glm::length(tan) > 0.0001f) {
                tan = glm::normalize(tan);
                float angle = glm::degrees(std::atan2(tan.x, tan.z)) + rotationOffset;
                m = glm::rotate(m, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
            }
        }
        return m;
    }

    float getT() const { return t; }
    void setT(float newT) { t = newT; }
    bool isAlignRotation() const { return alignRotation; }
    void setAlignRotation(bool a) { alignRotation = a; }
    void setRotationOffset(float off) { rotationOffset = off; }
    glm::vec3 getPointA() const { return pointA; }
    glm::vec3 getPointB() const { return pointB; }
    glm::vec3 getPointC() const { return pointC; }
    glm::vec3 getPointD() const { return pointD; }
};
