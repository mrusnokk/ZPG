/**
 * @file BezierSplineMovement.h
 * @brief Class representing movement along a general Bezier spline composed of multiple cubic segments.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "transform/Transformation.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>
#include <cmath>

struct BezierSegment {
    glm::vec3 p0;
    glm::vec3 p1;
    glm::vec3 p2;
    glm::vec3 p3;
};

class BezierSplineMovement : public Transformation {
private:
    std::vector<BezierSegment> segments;
    glm::mat4 A;
    float t;
    float speed;
    int direction;
    double lastTime;
    bool alignRotation;

    void getSegmentAndLocalT(int& idx, float& localT) const {
        int n = static_cast<int>(segments.size());
        idx = static_cast<int>(std::floor(t));
        localT = t - static_cast<float>(idx);
        if (idx >= n) {
            idx = n - 1;
            localT = 1.0f;
        }
        else if (idx < 0) {
            idx = 0;
            localT = 0.0f;
        }
    }

public:
    BezierSplineMovement(const std::vector<glm::vec3>& points, float speed = 0.5f, bool alignRotation = true)
        : t(0.0f), speed(speed), direction(1), alignRotation(alignRotation) {
        A = glm::mat4(
            glm::vec4(-1.0f,  3.0f, -3.0f, 1.0f),
            glm::vec4( 3.0f, -6.0f,  3.0f, 0.0f),
            glm::vec4(-3.0f,  3.0f,  0.0f, 0.0f),
            glm::vec4( 1.0f,  0.0f,  0.0f, 0.0f)
        );
        lastTime = glfwGetTime();

        for (size_t i = 0; i + 3 < points.size(); i += 3) {
            segments.push_back({ points[i], points[i + 1], points[i + 2], points[i + 3] });
        }
    }

    glm::vec3 getPosition() const {
        if (segments.empty()) return glm::vec3(0.0f);
        int idx;
        float localT;
        getSegmentAndLocalT(idx, localT);
        const BezierSegment& seg = segments[idx];
        glm::vec4 parameters(localT * localT * localT, localT * localT, localT, 1.0f);
        glm::mat4x3 B(seg.p0, seg.p1, seg.p2, seg.p3);
        return parameters * A * glm::transpose(B);
    }

    glm::vec3 getTangent() const {
        if (segments.empty()) return glm::vec3(0.0f, 0.0f, 1.0f);
        int idx;
        float localT;
        getSegmentAndLocalT(idx, localT);
        const BezierSegment& seg = segments[idx];
        glm::vec4 dParameters(3.0f * localT * localT, 2.0f * localT, 1.0f, 0.0f);
        glm::mat4x3 B(seg.p0, seg.p1, seg.p2, seg.p3);
        return dParameters * A * glm::transpose(B);
    }

    void update() {
        if (segments.empty()) return;
        double currentTime = glfwGetTime();
        if (lastTime > 0.0) {
            float dt = static_cast<float>(currentTime - lastTime);
            if (dt > 0.0f && dt < 0.1f) {
                float maxT = static_cast<float>(segments.size());
                t += direction * speed * dt;
                if (t >= maxT) {
                    t = maxT;
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
                float angle = glm::degrees(std::atan2(tan.x, tan.z));
                m = glm::rotate(m, glm::radians(angle), glm::vec3(0.0f, 1.0f, 0.0f));
            }
        }
        return m;
    }
};
