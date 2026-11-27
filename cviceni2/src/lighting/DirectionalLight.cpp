#include "lighting/DirectionalLight.h"

DirectionalLight::DirectionalLight(int index, glm::vec3 direction, glm::vec3 color, float intensity)
	: Light(index, glm::vec3(0.0f), color, intensity, LightType::DIRECTIONAL,
	        direction, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f) {}
