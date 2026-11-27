/**
 * @file PointLight.h
 * @brief Class representing a point light source.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "lighting/Light.h"

class PointLight : public Light {
public:
	PointLight(int index, glm::vec3 position, glm::vec3 color, float intensity = 1.0f,
	           float constant = 1.0f, float linear = 0.7f, float quadratic = 3.8f);
};
