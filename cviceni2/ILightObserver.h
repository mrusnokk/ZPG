#pragma once
#include <glm/glm.hpp>
#include "Light.h"

class ILightObserver {
public:
	virtual ~ILightObserver() = default;

	virtual void onLightChange(const Light& light) = 0;
};