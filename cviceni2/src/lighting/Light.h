#pragma once
#include <glm/glm.hpp>
#include <vector>
#include "lighting/ILightObserver.h"

class Light {
private:
	int index;
	glm::vec3 position;
	glm::vec3 color;
	float intensity;
	std::vector<ILightObserver*> observers;
public:
	Light(int index, glm::vec3 position, glm::vec3 color, float intensity) :
		index(index), position(position), color(color), intensity(intensity) {}
	~Light() = default;
	void notifyObservers() {
		for (ILightObserver* observer : observers) {
			observer->onLightChange(*this);
		}
	}
	glm::vec3 getPosition() const { return position; }
	glm::vec3 getColor() const { return color; }
	float getIntensity() const { return intensity; }
	glm::vec3 getDiffuse() const { return color * intensity; }
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
		notifyObservers();
	}
	void registerObserver(ILightObserver* observer) {
		observers.push_back(observer);
		observer->onLightChange(*this);
	}
	int getIndex() const { return index; }
};
