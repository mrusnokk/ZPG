#pragma once
#include "glm-master/glm/glm.hpp";
#include <glm/gtc/matrix_transform.hpp>
class Camera {
private:
	glm::mat4 viewMatrix;
	glm::mat4 projectionMatrix;
	
	glm::vec3 position;
	glm::vec3 front;
	glm::vec3 up;

	float yaw = -90.0f;
	float pitch = 0.0f;
public:
	Camera(glm::vec3 position = glm::vec3(0.0f, 2.0f, 8.0f));
	void setProjection(float fov, float aspectRatio, float nearPlane, float farPlane);
	void updateViewMatrix();
	glm::mat4 getViewMatrix();
	glm::mat4 getProjectionMatrix();
};