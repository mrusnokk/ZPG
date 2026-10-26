#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "ILightObserver.h"

class Light {
private:
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	std::vector<ILightObserver*> observers;
public:
	Light(glm::vec3 position, glm::vec3 color, float intensity) :
		position(position), color(color), intensity(intensity) {}
	~Light() = default;
	void notifyObservers() {
		for (ILightObserver* observer : observers) {
			observer->onLightChange(*this);
		}
	}
	glm::vec3 getPosition() const { return position; }
	glm::vec3 getColor() const { return color; }
	float getIntensity() const { return intensity; }
	void registerObserver(ILightObserver* observer) {
		observers.push_back(observer);
		observer->onLightChange(*this);
	}

};