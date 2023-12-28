#include "DemoTER/glwrapper/MSTexture.hpp"

MSTexture::MSTexture(int w, int h, int samples, bool hdr): samples{samples}, hdr{hdr} {
	glGenTextures(1, &id);
	setSize(w, h);

	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D_MULTISAMPLE, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
}

void MSTexture::setSize(int w, int h) {
	width = w;
	height = h;

	bind();

	GLenum internalFormat = GL_RGB;
	if(hdr) {
		internalFormat = GL_RGB16F;
	}

	glTexImage2DMultisample(GL_TEXTURE_2D_MULTISAMPLE, samples, internalFormat, width, height, GL_TRUE);
}

void MSTexture::bind(int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_2D_MULTISAMPLE, id);
}
