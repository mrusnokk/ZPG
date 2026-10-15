/**@file Camera.h
 * @brief Class representing a camera.
 * @author Michael Rusnok (rus0130)
 * @year 2026
 */
#pragma once
#include "glm-master/glm/glm.hpp";
#include <glm/gtc/matrix_transform.hpp>
#include "Application.h"
class Camera {
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	
	glm::vec3 eye;
	glm::vec3 center;
	glm::vec3 up;

	float alpha;
	float fi;
	float speed = 0.01f;
	float sensitivity = 0.1f;

public:
	Camera(glm::vec3 eye = glm::vec3(0.0f, 2.0f, 5.0f),
		float alpha = 90.0f,
		float fi = -90.0f
	);
	void setProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
	void updateViewMatrix();

	void toFront();
	void toBack();
	void toRight();
	void toLeft();

	void processMouseMovement(float x, float y);

	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};