#pragma once

class Camera;

class ICameraObserver {
public:
    virtual ~ICameraObserver() = default;

    virtual void onCameraChange(Camera* camera) = 0;
};
