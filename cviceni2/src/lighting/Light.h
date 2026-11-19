/**
 * @file Light.h
 * @brief Base class for light sources in the scene.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include <glm/glm.hpp>
#include <glm/gtc/constants.hpp>
#include <vector>
#include "lighting/ILightObserver.h"
#include "lighting/LightType.h"

class Light {
protected:
	int index;
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	bool enabled;
	float savedIntensity;
	LightType type;
	glm::vec3 direction;
	float cutOff;
	float outerCutOff;
	float constant;
	float linear;
	float quadratic;
	std::vector<ILightObserver*> observers;

public:
	Light(int index, glm::vec3 position, glm::vec3 color, float intensity,
	      LightType type = LightType::POINT,
	      glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f),
	      float cutOff = 0.9659258f,
	      float outerCutOff = 0.9396926f,
	      float constant = 1.0f, float linear = 0.7f, float quadratic = 3.8f) :
		index(index), position(position), color(color), intensity(intensity),
		enabled(intensity > 0.0f), savedIntensity(intensity > 0.0f ? intensity : 1.0f),
		type(type), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff),
		constant(constant), linear(linear), quadratic(quadratic) {}

	virtual ~Light() = default;

	void notifyObservers() {
		for (ILightObserver* observer : observers) {
			observer->onLightChange(*this);
		}
	}

	int getIndex() const { return index; }
	glm::vec3 getPosition() const { return position; }
	glm::vec3 getColor() const { return color; }
	float getIntensity() const { return intensity; }
	glm::vec3 getDiffuse() const { return color * intensity; }
	LightType getType() const { return type; }
	glm::vec3 getDirection() const { return direction; }
	float getCutOff() const { return cutOff; }
	float getOuterCutOff() const { return outerCutOff; }
	float getConstant() const { return constant; }
	float getLinear() const { return linear; }
	float getQuadratic() const { return quadratic; }

	bool isEnabled() const { return enabled; }

	virtual void setEnabled(bool enable) {
		if (this->enabled == enable) return;
		this->enabled = enable;
		if (this->enabled) {
			this->intensity = (this->savedIntensity > 0.0f) ? this->savedIntensity : 1.0f;
		}
		else {
			this->savedIntensity = (this->intensity > 0.0f) ? this->intensity : this->savedIntensity;
			this->intensity = 0.0f;
		}
		notifyObservers();
	}

	virtual void toggle() {
		setEnabled(!this->enabled);
	}

	void setPosition(const glm::vec3& pos) {
		this->position = pos;
		notifyObservers();
	}
	void setColor(const glm::vec3& col) {
		this->color = col;
		notifyObservers();
	}
	void setIntensity(float intens) {
		this->intensity = intens;
		if (intens > 0.0f) {
			this->savedIntensity = intens;
			this->enabled = true;
		}
		else {
			this->enabled = false;
		}
		notifyObservers();
	}
	void setDirection(const glm::vec3& dir) {
		this->direction = dir;
		notifyObservers();
	}
	void setType(LightType t) {
		this->type = t;
		notifyObservers();
	}
	void setCutOff(float innerAngleDeg) {
		this->cutOff = glm::cos(glm::radians(innerAngleDeg));
		notifyObservers();
	}
	void setOuterCutOff(float outerAngleDeg) {
		this->outerCutOff = glm::cos(glm::radians(outerAngleDeg));
		notifyObservers();
	}
	void setAttenuation(float c, float l, float q) {
		this->constant = c;
		this->linear = l;
		this->quadratic = q;
		notifyObservers();
	}

	void registerObserver(ILightObserver* observer) {
		observers.push_back(observer);
		observer->onLightChange(*this);
	}
};

#include "lighting/PointLight.h"
#include "lighting/DirectionalLight.h"
#include "lighting/SpotLight.h"
#include "lighting/Flashlight.h"
