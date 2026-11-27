/**
 * @file ILightObserver.h
 * @brief Interface for observers listening to light source changes.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include <glm/glm.hpp>

class Light;

class ILightObserver {
public:
	virtual ~ILightObserver() = default;
	virtual void onLightChange(const Light& light) = 0;
};
