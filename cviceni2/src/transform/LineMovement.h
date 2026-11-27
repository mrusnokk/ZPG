/**
 * @file LineMovement.h
 * @brief Class representing linear movement between two 3D points.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
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
    LineMovement(const glm::vec3& a, const glm::vec3& b, float speed = 0.5f);

    glm::vec3 getPosition() const;
    void update();
    glm::mat4 getMatrix() override;

    float getT() const;
    void setT(float newT);
    glm::vec3 getPointA() const;
    glm::vec3 getPointB() const;
};
