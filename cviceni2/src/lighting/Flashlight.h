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
	           float constant = 1.0f, float linear = 0.7f, float quadratic = 3.8f)
		: SpotLight(index,
		            (cam != nullptr) ? cam->getPosition() : glm::vec3(0.0f),
		            (cam != nullptr) ? cam->getFront() : glm::vec3(0.0f, 0.0f, -1.0f),
		            color, intensity, cutOffAngleDeg, outerCutOffAngleDeg, constant, linear, quadratic),
		  camera(cam)
	{
		if (this->camera != nullptr) {
			this->camera->obs_register(this);
		}
	}

	virtual ~Flashlight() {
		if (this->camera != nullptr) {
			this->camera->obs_remove(this);
		}
	}

	void onCameraChange(Camera* cam) override {
		if (!this->enabled || cam == nullptr) return;
		this->position = cam->getPosition();
		this->direction = cam->getFront();
		notifyObservers();
	}

	void setEnabled(bool enable) override {
		if (enable && this->camera != nullptr) {
			this->position = this->camera->getPosition();
			this->direction = this->camera->getFront();
		}
		Light::setEnabled(enable);
	}
};
