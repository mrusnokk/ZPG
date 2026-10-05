#pragma once
#include "glm-master/glm/glm.hpp";

class Transformation {
private:
    glm::vec3 position;
    glm::vec3 scale;
    glm::vec3 rotationAxis;
    float rotationAngle;

    glm::mat4 modelMatrix;
    void updateMatrix();

public:

	Transformation();

	void setPosition(float x, float y, float z);
	void setScale(float x, float y, float z);
	void setRotation(float angle, float axisX, float axisY, float axisZ);
    glm::mat4 getMatrix();
};