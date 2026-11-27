#include "lighting/Flashlight.h"

Flashlight::Flashlight(int index, Camera* cam, glm::vec3 color,
                       float intensity, float cutOffAngleDeg, float outerCutOffAngleDeg,
                       float constant, float linear, float quadratic)
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

Flashlight::~Flashlight() {
	if (this->camera != nullptr) {
		this->camera->obs_remove(this);
	}
}

void Flashlight::onCameraChange(Camera* cam) {
	if (!this->enabled || cam == nullptr) return;
	this->position = cam->getPosition();
	this->direction = cam->getFront();
	notifyObservers();
}

void Flashlight::setEnabled(bool enable) {
	if (enable && this->camera != nullptr) {
		this->position = this->camera->getPosition();
		this->direction = this->camera->getFront();
	}
	Light::setEnabled(enable);
}
