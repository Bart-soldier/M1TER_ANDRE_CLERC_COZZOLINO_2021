#include "DemoTER/CheckError.hpp"

void printStatus(GLenum glstatus) {
	switch(glstatus) {
		case GL_INVALID_ENUM: std::cout << "GL_INVALID_ENUM"; break;
		case GL_INVALID_VALUE: std::cout << "GL_INVALID_VALUE"; break;
		case GL_INVALID_OPERATION: std::cout << "GL_INVALID_OPERATION"; break;
		case GL_OUT_OF_MEMORY: std::cout << "GL_OUT_OF_MEMORY"; break;
		case GL_INVALID_FRAMEBUFFER_OPERATION: std::cout << "GL_INVALID_FRAMEBUFFER_OPERATION"; break;
		default: std::cout << "UNKNOWN"; break;
	}
}

void dumpGlErrorStack() {
	GLenum glstatus;

	while(1) {
		glstatus = glGetError();

		if(glstatus == GL_NO_ERROR) {
			std::cout << "No GL error" << std::endl;
			return;
		}

		std::cout << "GL error > ";
		printStatus(glstatus);
		std::cout << std::endl;
	}
}

void dumpLastGlError() {
	GLenum lastStatus = glGetError();

	if(lastStatus == GL_NO_ERROR) {
		std::cout << "No GL error" << std::endl;
		return;
	}

	GLenum status = lastStatus;
	while(status != GL_NO_ERROR) {
		lastStatus = status;
		status = glGetError();
	}

	std::cout << "GL error > ";
	printStatus(lastStatus);
	std::cout << std::endl;

}
