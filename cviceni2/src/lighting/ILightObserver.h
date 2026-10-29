#pragma once
#include <glm/glm.hpp>
class Light;
class ILightObserver {
public:
	virtual ~ILightObserver() = default;

	virtual void onLightChange(const Light& light) = 0;
};