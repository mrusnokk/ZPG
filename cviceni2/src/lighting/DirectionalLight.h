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
	DirectionalLight(int index, glm::vec3 direction, glm::vec3 color, float intensity = 1.0f);
};
