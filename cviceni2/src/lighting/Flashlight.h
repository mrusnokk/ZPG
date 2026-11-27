/**
 * @file Flashlight.h
 * @brief Class representing a flashlight attached to a camera via Observer pattern.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "lighting/SpotLight.h"
#include "camera/ICameraObserver.h"
#include "camera/Camera.h"

class Flashlight : public SpotLight, public ICameraObserver {
private:
	Camera* camera = nullptr;

public:
	Flashlight(int index, Camera* cam, glm::vec3 color = glm::vec3(1.0f, 1.0f, 0.9f),
	           float intensity = 3.0f, float cutOffAngleDeg = 12.0f, float outerCutOffAngleDeg = 18.0f,
	           float constant = 1.0f, float linear = 0.7f, float quadratic = 3.8f);
	virtual ~Flashlight();

	void onCameraChange(Camera* cam) override;
	void setEnabled(bool enable) override;
};
