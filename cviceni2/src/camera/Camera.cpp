#include "camera/Camera.h"

Camera::Camera(glm::vec3 eye, float alpha, float fi) {
	this->eye = eye;
	this->up = glm::vec3(0.0f, 1.0f, 0.0f);
	this->alpha = alpha;
	this->fi = fi;

	processMouseMovement(0.0f, 0.0f);
    this->projectionMatrix = glm::mat4(1.0f);
}
void Camera::obs_register(ICameraObserver* obs) {
	observers.push_back(obs);
	obs->onCameraChange(viewMatrix, projectionMatrix, eye);
}
void Camera::obs_remove(ICameraObserver* obs) {
	std::erase(observers, obs);
}

void Camera::setProjection(float fov, float aspectRatio, float nearPlane, float farPlane) {
	this->fov = fov;
	this->nearPlane = nearPlane;
	this->farPlane = farPlane;
	this->projectionMatrix = glm::perspective(glm::radians(fov), aspectRatio, nearPlane, farPlane);
	notifyObservers();
}

void Camera::setAspectRatio(float aspectRatio) {
	setProjection(fov, aspectRatio, nearPlane, farPlane);
}

void Camera::notifyObservers() {
	for (auto* obs : observers) {
		obs->onCameraChange(viewMatrix, projectionMatrix, eye);
	}
}

void Camera::updateViewMatrix() {
	this->viewMatrix = glm::lookAt(eye, eye + center, up);
	notifyObservers();

}

void Camera::toFront() {
	eye += glm::normalize(center) * speed;
	updateViewMatrix();
}

void Camera::toBack() {
	eye -= glm::normalize(center) * speed;
	updateViewMatrix();
}

void Camera::toLeft() {
	eye -= glm::normalize(glm::cross(center, up)) * speed;
	updateViewMatrix();
}

void Camera::toRight() {
	eye += glm::normalize(glm::cross(center, up)) * speed;
	updateViewMatrix();
}

void Camera::processMouseMovement(float x, float y) {

	fi += x * sensitivity;
	alpha -= y * sensitivity;

	if (alpha > 179.0f)alpha = 179.0f;
	if (alpha < 1.0f)alpha = 1.0f;

	glm::vec3 newTarget;
	newTarget.x = sin(glm::radians(alpha)) * cos(glm::radians(fi));
	newTarget.y = cos(glm::radians(alpha));
	newTarget.z = sin(glm::radians(alpha)) * sin(glm::radians(fi));
	this->center = glm::normalize(newTarget);
	updateViewMatrix();
}

glm::mat4 Camera::getViewMatrix() {
	return this->viewMatrix;
}
glm::mat4 Camera::getProjectionMatrix() {
	return this->projectionMatrix;
}
glm::vec3 Camera::getPosition() {
	return this->eye;
}