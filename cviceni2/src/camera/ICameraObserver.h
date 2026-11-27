/**
 * @file ICameraObserver.h
 * @brief Interface for observers listening to camera changes.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once

class Camera;

class ICameraObserver {
public:
    virtual ~ICameraObserver() = default;
    virtual void onCameraChange(Camera* camera) = 0;
};
