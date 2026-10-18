#pragma once
#include <glm/glm.hpp>

class ICameraObserver {
public:
    virtual ~ICameraObserver() = default;

    virtual void onCameraChange(const glm::mat4& view, const glm::mat4& projection) = 0;
};