/**
 * @file Transformation.h
 * @brief Abstract class for all transformations.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "glm-master/glm/glm.hpp"

class Transformation {
public:
	virtual glm::mat4 getMatrix() = 0;
	virtual ~Transformation() = default;
};