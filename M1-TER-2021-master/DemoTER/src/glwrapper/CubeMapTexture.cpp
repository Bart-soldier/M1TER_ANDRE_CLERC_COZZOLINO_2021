#include "DemoTER/glwrapper/CubeMapTexture.hpp"
#include "stbimage/stb_image.h"
#include <iostream>
#include "DemoTER/config.hpp"

CubeMapTexture::Options::Options(): wrapS{GL_CLAMP_TO_EDGE}, wrapT{GL_CLAMP_TO_EDGE}, wrapR{GL_CLAMP_TO_EDGE}, minFilter{GL_LINEAR}, magFilter{GL_LINEAR} {}

CubeMapTexture::CubeMapTexture(TexPaths &paths, bool correctGamma, Options options) {
    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    setOptions(options);

    std::string faces[6] {
        std::string(RESOURCES_DIRECTORY).append(paths.right),
        std::string(RESOURCES_DIRECTORY).append(paths.left),
        std::string(RESOURCES_DIRECTORY).append(paths.top),
        std::string(RESOURCES_DIRECTORY).append(paths.bot),
        std::string(RESOURCES_DIRECTORY).append(paths.front),
        std::string(RESOURCES_DIRECTORY).append(paths.back)
    };

    int textureNrChannels;
    for(unsigned int i = 0; i < 6; i++) {
        std::cout << "Chargement de " << faces[i] << std::endl;
        stbi_set_flip_vertically_on_load(true);
        unsigned char *data = stbi_load(faces[i].c_str(), &width, &height, &textureNrChannels, 0);

        GLenum format = GL_RGB;
        GLenum internalFormat = GL_RGBA;
        if(data) {
            if(correctGamma) {
                switch(textureNrChannels) {
                    case 1: format = GL_RED; internalFormat = GL_RED; break;
                    case 3: format = GL_RGB; internalFormat = GL_SRGB; break;
                    case 4: format = GL_RGBA; internalFormat = GL_SRGB_ALPHA;
                }
            } else {
                switch(textureNrChannels) {
                    case 1: format = GL_RED; internalFormat = GL_RED; break;
                    case 3: format = GL_RGB; internalFormat = GL_RGB; break;
                    case 4: format = GL_RGBA; internalFormat = GL_RGBA;
                }
            }

            glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, width, height, 0, format, GL_UNSIGNED_BYTE, data);
        } else {
            std::cout << "Cubemap texture failed to load at path: " << faces[i] << std::endl;
        }

        stbi_image_free(data);
    }
}

CubeMapTexture::CubeMapTexture(int w, int h, bool hdr, Options options) {
    width = w;
    height = h;

    glGenTextures(1, &id);
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);

    setOptions(options);

    GLenum internalFormat = GL_RGB;
    if(hdr) internalFormat = GL_RGB16F;
    for(unsigned int i = 0; i < 6; i++) {
        glTexImage2D(GL_TEXTURE_CUBE_MAP_POSITIVE_X + i, 0, internalFormat, width, height, 0, GL_RGB, GL_FLOAT, nullptr);
    }
}

void CubeMapTexture::createMips() {
    glBindTexture(GL_TEXTURE_CUBE_MAP, id);
    glGenerateMipmap(GL_TEXTURE_CUBE_MAP);
}

void CubeMapTexture::setOptions(Options options) {
	bind();
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_S, options.wrapS);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_T, options.wrapT);
    glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_WRAP_R, options.wrapR);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MIN_FILTER, options.minFilter);
	glTexParameteri(GL_TEXTURE_CUBE_MAP, GL_TEXTURE_MAG_FILTER, options.magFilter);
}

void CubeMapTexture::bind(int unit) {
	glActiveTexture(GL_TEXTURE0 + unit);
	glBindTexture(GL_TEXTURE_CUBE_MAP, id);
}

void CubeMapTexture::setSize(int w, int h) {

}