#include "DemoTER/utils/Mouse.hpp"
#include <GLFW/glfw3.h>

std::shared_ptr<Mouse> Mouse::instance = nullptr;

Mouse::Mouse(): position{0, 0}, velocity{0, 0}, scrollVelocity{0, 0} {
	for(int i = 0; i < 3; ++i) pressedKeys[i] = false;
}

void Mouse::init() {
	if(instance == nullptr)	instance = std::shared_ptr<Mouse>(new Mouse{});
}

void Mouse::buttonEvent(int button, int action, int mods) {
	if(action == GLFW_PRESS) {
		if(button == GLFW_MOUSE_BUTTON_LEFT)
			instance->pressedKeys[Mouse::LEFT] = true;
	
		if(button == GLFW_MOUSE_BUTTON_MIDDLE)
			instance->pressedKeys[Mouse::MIDDLE] = true;

		if(button == GLFW_MOUSE_BUTTON_RIGHT)
			instance->pressedKeys[Mouse::RIGHT] = true;
	}

	if(action == GLFW_RELEASE) {
		if(button == GLFW_MOUSE_BUTTON_LEFT)
			instance->pressedKeys[Mouse::LEFT] = false;

		if(button == GLFW_MOUSE_BUTTON_MIDDLE)
			instance->pressedKeys[Mouse::MIDDLE] = false;

		if(button == GLFW_MOUSE_BUTTON_RIGHT)
			instance->pressedKeys[Mouse::RIGHT] = false;
	}
}

void Mouse::moveEvent(double x, double y) {
	instance->velocity[0] = x - instance->position[0];
	instance->velocity[1] = instance->position[1] - y;

	instance->position[0] = x;
	instance->position[1] = y;
}

void Mouse::scrollEvent(double xoffset, double yoffset) {
	instance->scrollVelocity[0] = xoffset;
	instance->scrollVelocity[1] = yoffset;
}

void Mouse::update() {
	instance->velocity[0] = 0;
	instance->velocity[1] = 0;

	instance->scrollVelocity[0] = 0;
	instance->scrollVelocity[1] = 0;
}

std::shared_ptr<Mouse> Mouse::getInstance() {
	return instance;
}

bool Mouse::isPressed(int key) {
	return pressedKeys[key];
}

glm::vec2 &Mouse::getVelocity() {
	return velocity;
}

glm::vec2 &Mouse::getScrollVelocity() {
	return scrollVelocity;
}

glm::vec2 &Mouse::getPosition() {
	return position;
}
