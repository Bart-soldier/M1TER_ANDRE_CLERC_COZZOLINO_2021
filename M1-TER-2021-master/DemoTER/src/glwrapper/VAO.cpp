#include "DemoTER/glwrapper/VAO.hpp"

VAO::VAO(): drawMode{GL_TRIANGLES}, length {0} {
	glGenVertexArrays(1, &id);
}

VAO::~VAO() {
	glDeleteVertexArrays(1, &id);
}

void VAO::addVBO(std::shared_ptr<VBO> vbo) {
	if(length < vbo->getLength()) length = vbo->getLength();
	vbos.push_back(vbo);
}

void VAO::setDrawMode(GLuint mode) {
	drawMode = mode;
}

void VAO::bind() {
	glBindVertexArray(id);
}

void VAO::unbind() {
	glBindVertexArray(0);
}

void VAO::prepare() {
	bind();
	for(std::shared_ptr<VBO> vbo : vbos) {
		vbo->bind();
		glVertexAttribPointer(vbo->getLocation(), vbo->getTupleSize(), GL_FLOAT, GL_FALSE, 0, 0);
		glEnableVertexAttribArray(vbo->getLocation());
	}
	unbind();
}

void VAO::draw() {
	bind();
	glDrawArrays(drawMode, 0, length);
	//glDrawArraysInstanced(drawMode, 0, length, 1);
	unbind();
}
