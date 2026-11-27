#include "transform/BezierSplineMovement.h"
#include <cmath>

void BezierSplineMovement::getSegmentAndLocalT(int& idx, float& localT) const {
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

BezierSplineMovement::BezierSplineMovement(const std::vector<Translate*>& points, float speed, bool alignRotation)
    : t(0.0f), speed(speed), direction(1), alignRotation(alignRotation) {
    A = glm::mat4(
        glm::vec4(-1.0f,  3.0f, -3.0f, 1.0f),
        glm::vec4( 3.0f, -6.0f,  3.0f, 0.0f),
        glm::vec4(-3.0f,  3.0f,  0.0f, 0.0f),
        glm::vec4( 1.0f,  0.0f,  0.0f, 0.0f)
    );
    lastTime = glfwGetTime();

    for (size_t i = 0; i + 3 < points.size(); i += 3) {
        BezierSegment seg{ points[i], points[i + 1], points[i + 2], points[i + 3] };
        seg.p0->addRef();
        seg.p1->addRef();
        seg.p2->addRef();
        seg.p3->addRef();
        segments.push_back(seg);
    }
}

BezierSplineMovement::~BezierSplineMovement() {
    for (BezierSegment& seg : segments) {
        seg.p0->release();
        seg.p1->release();
        seg.p2->release();
        seg.p3->release();
    }
}

glm::vec3 BezierSplineMovement::getPosition() const {
    if (segments.empty()) return glm::vec3(0.0f);
    int idx;
    float localT;
    getSegmentAndLocalT(idx, localT);
    const BezierSegment& seg = segments[idx];
    glm::vec4 parameters(localT * localT * localT, localT * localT, localT, 1.0f);
    glm::mat4x3 B(seg.p0->getPosition(), seg.p1->getPosition(), seg.p2->getPosition(), seg.p3->getPosition());
    return parameters * A * glm::transpose(B);
}

glm::vec3 BezierSplineMovement::getTangent() const {
    if (segments.empty()) return glm::vec3(0.0f, 0.0f, 1.0f);
    int idx;
    float localT;
    getSegmentAndLocalT(idx, localT);
    const BezierSegment& seg = segments[idx];
    glm::vec4 dParameters(3.0f * localT * localT, 2.0f * localT, 1.0f, 0.0f);
    glm::mat4x3 B(seg.p0->getPosition(), seg.p1->getPosition(), seg.p2->getPosition(), seg.p3->getPosition());
    return dParameters * A * glm::transpose(B);
}

void BezierSplineMovement::update() {
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

glm::mat4 BezierSplineMovement::getMatrix() {
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
