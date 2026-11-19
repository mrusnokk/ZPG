/**
 * @file DirectionalLight.h
 * @brief Class representing a directional light source.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "lighting/Light.h"

class DirectionalLight : public Light {
public:
	DirectionalLight(int index, glm::vec3 direction, glm::vec3 color, float intensity = 1.0f)
		: Light(index, glm::vec3(0.0f), color, intensity, LightType::DIRECTIONAL,
		        direction, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f) {}
};
