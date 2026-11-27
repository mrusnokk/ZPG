/**
 * @file BezierSplineMovement.h
 * @brief Class representing movement along a general Bezier spline composed of multiple cubic segments.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "transform/Transformation.h"
#include "transform/Translate.h"
#include <glad/gl.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <vector>

struct BezierSegment {
    Translate* p0;
    Translate* p1;
    Translate* p2;
    Translate* p3;
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

    void getSegmentAndLocalT(int& idx, float& localT) const;

public:
    BezierSplineMovement(const std::vector<Translate*>& points, float speed = 0.5f, bool alignRotation = true);
    ~BezierSplineMovement() override;

    glm::vec3 getPosition() const;
    glm::vec3 getTangent() const;
    void update();
    glm::mat4 getMatrix() override;
};
