#include "lighting/PointLight.h"

PointLight::PointLight(int index, glm::vec3 position, glm::vec3 color, float intensity,
                       float constant, float linear, float quadratic)
	: Light(index, position, color, intensity, LightType::POINT,
	        glm::vec3(0.0f, -1.0f, 0.0f), 0.0f, 0.0f, constant, linear, quadratic) {}
