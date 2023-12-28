#include "DemoTER/FlatShader.hpp"

FlatShader::FlatShader(): Shader{"shaders/flat.vert", "shaders/flat.frag"} {
	fetchUniformLocations();

	bind();
	sendFloat(FlatShader::U_EXPOSURE, 1);
}

void FlatShader::fetchUniformLocations() {
	uniformLocations = new GLuint[4];

	uniformLocations[U_MODEL] = queryUniformLocation("M");
	uniformLocations[U_PV] = queryUniformLocation("PV");
	uniformLocations[U_COLOR] = queryUniformLocation("color");
	uniformLocations[U_EXPOSURE] = queryUniformLocation("exposure");
}

void FlatShader::setCamera(Camera *camera) {
	sendMat4(U_PV, camera->getPVMatrix());
}

void FlatShader::setExposure(float e) {
	sendFloat(FlatShader::U_EXPOSURE, e);
}
