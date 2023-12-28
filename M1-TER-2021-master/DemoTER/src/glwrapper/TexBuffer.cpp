#include "DemoTER/glwrapper/TexBuffer.hpp"

TexBuffer::~TexBuffer() {
	glDeleteTextures(1, &id);
}

int TexBuffer::getWidth() const {
	return width;
}

int TexBuffer::getHeight() const {
	return height;
}

GLuint TexBuffer::getId() {
	return id;
}