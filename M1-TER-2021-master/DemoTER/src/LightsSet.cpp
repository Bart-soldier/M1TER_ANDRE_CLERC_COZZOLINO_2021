#include "DemoTER/LightsSet.hpp"


LightsSet::Light::Light(): color{1, 1, 1}, intensity{1}, on{true} {

}

void LightsSet::Light::setColor(float r, float g, float b) {
	color = {r, g, b};
}

glm::vec3 &LightsSet::Light::getColor() {
	return color;
}

void LightsSet::Light::setIntensity(float i) {
	intensity = i;
}

float& LightsSet::Light::getIntensity() {
	return intensity;
}

void LightsSet::Light::turnOn() {
	on = true;
}

void LightsSet::Light::turnOff() {
	on = false;
}

void LightsSet::Light::setOn(bool o) {
	on = o;
}

bool LightsSet::Light::isOn() {
	return on;
}

glm::vec3 LightsSet::Light::getLux() {
	if(on) return color * intensity;
	else return {0, 0, 0};
}

////////////////////////////////////////////////////////////////////////////////

LightsSet::LightsSet(int count): lightPositionsBuffer{count}, lightColorsBuffer{count}, lights{count} {
	update();
}

int LightsSet::getLightCount() {
	return lightPositionsBuffer.size();
}

LightsSet::Light &LightsSet::light(int index) {
	return lights[index];
}

void LightsSet::update() {
	for(int i = 0; i < lightPositionsBuffer.size(); ++i) {
		lightPositionsBuffer[i] = lights[i].getPosition();
		lightColorsBuffer[i] = lights[i].getLux();
	}
}

std::vector<glm::vec3> &LightsSet::getLightPositions() {
	return lightPositionsBuffer;
}

std::vector<glm::vec3> &LightsSet::getLightColors() {
	return lightColorsBuffer;
}
