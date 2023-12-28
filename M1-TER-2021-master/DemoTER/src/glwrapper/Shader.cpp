#include "DemoTER/glwrapper/Shader.hpp"
#include "DemoTER/config.hpp"

Shader::Shader(const char *vertexPath, const char *fragmentPath) {
    // 1. retrieve the vertex/fragment source code from filePath
    std::string vertexCode;
    std::string fragmentCode;
    std::ifstream vShaderFile;
    std::ifstream fShaderFile;
    // ensure ifstream objects can throw exceptions:
    vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
    fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);

    try {
        // open files
        std::cout << "Chargement de " << vertexPath << " et " << fragmentPath << std::endl;
        vShaderFile.open(std::string(RESOURCES_DIRECTORY).append(vertexPath).c_str());
        fShaderFile.open(std::string(RESOURCES_DIRECTORY).append(fragmentPath).c_str());

        std::stringstream vShaderStream, fShaderStream;
        // read file's buffer contents into streams
        vShaderStream << vShaderFile.rdbuf();
        fShaderStream << fShaderFile.rdbuf();
        // close file handlers
        vShaderFile.close();
        fShaderFile.close();
        // convert stream into string
        vertexCode = vShaderStream.str();
        fragmentCode = fShaderStream.str();

    } catch(std::ifstream::failure &e) {
        std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ - " << e.what() << std::endl;
    }

    const char *vShaderCode = vertexCode.c_str();
    const char *fShaderCode = fragmentCode.c_str();
    // 2. compile shaders
    unsigned int vertex, fragment;
    // vertex shader
    vertex = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertex, 1, &vShaderCode, NULL);
    glCompileShader(vertex);
    checkCompileErrors(vertex, "VERTEX");
    // fragment Shader
    fragment = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragment, 1, &fShaderCode, NULL);
    glCompileShader(fragment);
    checkCompileErrors(fragment, "FRAGMENT");
    // if geometry shader is given, compile geometry shader
    unsigned int geometry = 0;

    // shader Program
    id = glCreateProgram();
    glAttachShader(id, vertex);
    glAttachShader(id, fragment);
    glLinkProgram(id);
    checkCompileErrors(id, "PROGRAM");
    // delete the shaders as they're linked into our program now and no longer necessery
    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

void Shader::checkCompileErrors(GLuint shader, std::string type) {
    GLint success;
    GLchar infoLog[1024];
    if(type != "PROGRAM") {
        glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
        if(!success) {
            glGetShaderInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    } else {
        glGetProgramiv(shader, GL_LINK_STATUS, &success);
        if(!success) {
            glGetProgramInfoLog(shader, 1024, NULL, infoLog);
            std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
        }
    }
}

Shader::~Shader() {
    delete uniformLocations;
    glDeleteProgram(id);
}

GLuint Shader::queryUniformLocation(const char *name) {
    return glGetUniformLocation(id, name);
}

void Shader::bind() const {
    glUseProgram(id);
}

void Shader::sendInt(GLuint uid, int value) const {
    glUniform1i(uniformLocations[uid], value);
}

void Shader::sendFloat(GLuint uid, float value) const {
    glUniform1f(uniformLocations[uid], value);
}

void Shader::sendVec2(GLuint uid, const glm::vec2 &value) const {
    glUniform2fv(uniformLocations[uid], 1, &value[0]);
}

void Shader::sendVec3(GLuint uid, const glm::vec3 &value) const {
    glUniform3fv(uniformLocations[uid], 1, &value[0]);
}

void Shader::sendVec3(GLuint uid, const std::vector<glm::vec3> &values) const {
    glUniform3fv(uniformLocations[uid], values.size(), &values[0][0]);
}

void Shader::sendMat4(GLuint uid, const glm::mat4 &mat) const {
    glUniformMatrix4fv(uniformLocations[uid], 1, GL_FALSE, &mat[0][0]);
}

void Shader::sendBool(GLuint uid, const bool value) const {
    glUniform1i(uniformLocations[uid], value);
}
