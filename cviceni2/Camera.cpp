#include "Camera.h"

Camera::Camera(glm::vec3 position) {
    this->position = position;
    this->front = glm::vec3(0.0f, 0.0f, -1.0f);
    this->up = glm::vec3(0.0f, 1.0f, 0.0f);

    this->yaw = -90.0f;
    this->pitch = 0.0f;

    updateViewMatrix();
    this->projectionMatrix = glm::mat4(1.0f);
}
void Camera::setProjection(float fov, float aspectRatio, float nearPlane, float farPlane) {
	this->projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
}
void Camera::updateViewMatrix() {
	this->viewMatrix = glm::lookAt(position, position + front, up);
}
glm::mat4 Camera::getViewMatrix() {
	return this->viewMatrix;
}
glm::mat4 Camera::getProjectionMatrix() {
	return this->projectionMatrix;
}