#include "lighting/Light.h"

Light::Light(int index, glm::vec3 position, glm::vec3 color, float intensity,
             LightType type, glm::vec3 direction, float cutOff, float outerCutOff,
             float constant, float linear, float quadratic)
	: index(index), position(position), color(color), intensity(intensity),
	  enabled(intensity > 0.0f), savedIntensity(intensity > 0.0f ? intensity : 1.0f),
	  type(type), direction(direction), cutOff(cutOff), outerCutOff(outerCutOff),
	  constant(constant), linear(linear), quadratic(quadratic) {}

void Light::notifyObservers() {
	for (ILightObserver* observer : observers) {
		observer->onLightChange(*this);
	}
}

int Light::getIndex() const { return index; }
glm::vec3 Light::getPosition() const { return position; }
glm::vec3 Light::getColor() const { return color; }
float Light::getIntensity() const { return intensity; }
glm::vec3 Light::getDiffuse() const { return color * intensity; }
LightType Light::getType() const { return type; }
glm::vec3 Light::getDirection() const { return direction; }
float Light::getCutOff() const { return cutOff; }
float Light::getOuterCutOff() const { return outerCutOff; }
float Light::getConstant() const { return constant; }
float Light::getLinear() const { return linear; }
float Light::getQuadratic() const { return quadratic; }
bool Light::isEnabled() const { return enabled; }

void Light::setEnabled(bool enable) {
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

void Light::toggle() {
	setEnabled(!this->enabled);
}

void Light::setPosition(const glm::vec3& pos) {
	this->position = pos;
	notifyObservers();
}

void Light::setColor(const glm::vec3& col) {
	this->color = col;
	notifyObservers();
}

void Light::setIntensity(float intens) {
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

void Light::setDirection(const glm::vec3& dir) {
	this->direction = dir;
	notifyObservers();
}

void Light::setType(LightType t) {
	this->type = t;
	notifyObservers();
}

void Light::setCutOff(float innerAngleDeg) {
	this->cutOff = glm::cos(glm::radians(innerAngleDeg));
	notifyObservers();
}

void Light::setOuterCutOff(float outerAngleDeg) {
	this->outerCutOff = glm::cos(glm::radians(outerAngleDeg));
	notifyObservers();
}

void Light::setAttenuation(float c, float l, float q) {
	this->constant = c;
	this->linear = l;
	this->quadratic = q;
	notifyObservers();
}

void Light::registerObserver(ILightObserver* observer) {
	observers.push_back(observer);
	observer->onLightChange(*this);
}
