#pragma once
#include "glm-master/glm/glm.hpp";

class Transformation {
public:
	virtual glm::mat4 getMatrix() = 0;
	virtual ~Transformation() = default;
};