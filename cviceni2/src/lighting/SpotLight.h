/**
 * @file SpotLight.h
 * @brief Class representing a spot light source.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "lighting/Light.h"

class SpotLight : public Light {
public:
	SpotLight(int index, glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity = 1.0f,
	          float cutOffAngleDeg = 15.0f, float outerCutOffAngleDeg = 20.0f,
	          float constant = 1.0f, float linear = 0.7f, float quadratic = 3.8f)
		: Light(index, position, color, intensity, LightType::SPOT,
		        direction, glm::cos(glm::radians(cutOffAngleDeg)), glm::cos(glm::radians(outerCutOffAngleDeg)),
		        constant, linear, quadratic) {}
};
