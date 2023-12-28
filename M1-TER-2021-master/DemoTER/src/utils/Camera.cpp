#include "DemoTER/utils/Camera.hpp"

Camera::Camera(): fov{70}, near{.01}, far{100.}, ratio{1.},
center{0, 0, 0}, eye{0, 0, 1}, up{0, 1, 0},
projectionMatrix{}, viewMatrix{}, pvMatrix{} {
	updateProjection();
}

void Camera::setFrustum(float f, float r, float n, float fa) {
	fov = f;
	ratio = r;
	near = n;
	far = fa;
	updateProjection();
}

void Camera::setRatio(float r) {
	ratio = r;
	updateProjection();
}

void Camera::updateProjection() {
	projectionMatrix = glm::perspective(fov, ratio, near, far);
}

glm::mat4x4 &Camera::getViewMatrix() {
	return viewMatrix;
}

glm::mat4x4 &Camera::getProjection() {
	return projectionMatrix;
}

glm::mat4x4 &Camera::getPVMatrix() {
	return pvMatrix;
}

glm::vec3 &Camera::getPosition() {
	return eye;
}
