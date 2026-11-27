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
	      float constant = 1.0f, float linear = 0.7f, float quadratic = 3.8f);
	virtual ~Light() = default;

	void notifyObservers();

	int getIndex() const;
	glm::vec3 getPosition() const;
	glm::vec3 getColor() const;
	float getIntensity() const;
	glm::vec3 getDiffuse() const;
	LightType getType() const;
	glm::vec3 getDirection() const;
	float getCutOff() const;
	float getOuterCutOff() const;
	float getConstant() const;
	float getLinear() const;
	float getQuadratic() const;
	bool isEnabled() const;

	virtual void setEnabled(bool enable);
	virtual void toggle();

	void setPosition(const glm::vec3& pos);
	void setColor(const glm::vec3& col);
	void setIntensity(float intens);
	void setDirection(const glm::vec3& dir);
	void setType(LightType t);
	void setCutOff(float innerAngleDeg);
	void setOuterCutOff(float outerAngleDeg);
	void setAttenuation(float c, float l, float q);

	void registerObserver(ILightObserver* observer);
};
