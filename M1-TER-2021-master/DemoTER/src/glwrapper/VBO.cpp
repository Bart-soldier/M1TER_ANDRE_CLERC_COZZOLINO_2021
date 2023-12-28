#include "DemoTER/glwrapper/VBO.hpp"

VBO::VBO(const std::vector<float> &data, int tupleSize, GLuint attributeLocation): tupleSize{tupleSize}, location{attributeLocation} {
	glGenBuffers(1, &id);
	bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(float), data.data(), GL_STATIC_DRAW);
	length = data.size() / tupleSize;
}

template<typename T> void VBO::build(const std::vector<T> &data) {
	glGenBuffers(1, &id);
	bind();
	glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), &data[0], GL_STATIC_DRAW);
	tupleSize = sizeof(T) / sizeof(float);
	length = data.size();
}

VBO::VBO(const std::vector<float> &data, GLuint attributeLocation): location{attributeLocation} {
	build(data);
}

VBO::VBO(const std::vector<glm::vec2> &data, GLuint attributeLocation): location{attributeLocation} {
	build(data);
}

VBO::VBO(const std::vector<glm::vec3> &data, GLuint attributeLocation): location{attributeLocation} {
	build(data);
}

VBO::VBO(const std::vector<glm::vec4> &data, GLuint attributeLocation): location{attributeLocation} {
	build(data);
}

VBO::~VBO() {
	glDeleteBuffers(1, &id);
}

int VBO::getTupleSize() {
	return tupleSize;
}

int VBO::getLength() {
	return length;
}

GLuint VBO::getLocation() {
	return location;
}

void VBO::bind() {
	glBindBuffer(GL_ARRAY_BUFFER, id);
}
