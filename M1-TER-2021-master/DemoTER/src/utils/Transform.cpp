#include "DemoTER/utils/Transform.hpp"

Transform::Transform(): position{0, 0, 0}, rotation{1, 0, 0, 0}, matrix{1}, origin{1} {}

void Transform::setOrigin(glm::mat4x4 &o) {
	origin = o;
}

void Transform::move(float dx, float dy, float dz) {
	position += glm::vec3{dx, dy, dz};
}

void Transform::setPosition(float x, float y, float z) {
	position = {x, y, z};
}

glm::vec3 &Transform::getPosition() {
	return position;
}

void Transform::rotateX(float a) {
	rotation *= glm::angleAxis(a, glm::vec3{-1, 0, 0});
}

void Transform::rotateY(float a) {
	rotation *= glm::angleAxis(a, glm::vec3{0, -1, 0});
}

void Transform::rotateZ(float a) {
	rotation *= glm::angleAxis(a, glm::vec3{0, 0, -1});
}

void Transform::setRotationZYX(float ax, float ay, float az) {
	rotation = {1, 0, 0, 0};
	rotateZ(az);
	rotateY(ay);
	rotateX(ax);
}

glm::quat &Transform::getRotation() {
	return rotation;
}

glm::mat4x4 &Transform::toMatrix() {
	glm::mat4 &&rotate = glm::toMat4(rotation);
	glm::mat4 &&translate = glm::translate(glm::mat4(1.), position);
	matrix = origin * translate * rotate;
	return matrix;
}
