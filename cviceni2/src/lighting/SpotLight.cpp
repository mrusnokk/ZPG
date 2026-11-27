#include "lighting/SpotLight.h"

SpotLight::SpotLight(int index, glm::vec3 position, glm::vec3 direction, glm::vec3 color, float intensity,
                     float cutOffAngleDeg, float outerCutOffAngleDeg,
                     float constant, float linear, float quadratic)
	: Light(index, position, color, intensity, LightType::SPOT,
	        direction, glm::cos(glm::radians(cutOffAngleDeg)), glm::cos(glm::radians(outerCutOffAngleDeg)),
	        constant, linear, quadratic) {}
