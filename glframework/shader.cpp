#include "shader.h"
#include "../wrapper/checkError.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

Shader::Shader(const char* vertesPath,const char* fragmentPath)
{
    std::string vertexCode = readFile(vertesPath);
    std::string fragmentCode = readFile(fragmentPath);

    const char* vertexShaderSource = vertexCode.c_str();
    const char* fragmentShaderSource = fragmentCode.c_str();

    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    //输入Shader程序代码
    glShaderSource(vertex, 1, &vertexShaderSource, NULL);
    glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

    //Shader代码编译
    GL_CALL(glCompileShader(vertex));
    checkShaderErrors(vertex, "COMPILE");

    GL_CALL(glCompileShader(fragment));
    checkShaderErrors(fragment, "COMPILE");

    //创建Program
    //GLuint program = glCreateProgram();
    mProgram = glCreateProgram();

    //编译好的结果放入Program
    glAttachShader(mProgram, vertex);
    glAttachShader(mProgram, fragment);

    //链接
    glLinkProgram(mProgram);
    checkShaderErrors(mProgram, "LINK");

    glDeleteShader(vertex);
    glDeleteShader(fragment);
}

Shader::~Shader()
{
}

void Shader::begin() const
{
    GL_CALL(glUseProgram(mProgram));
}

void Shader::end() const
{
    GL_CALL(glUseProgram(0));
}

void Shader::setUniformFloat(const std::string name, const float& value) const
{
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniform1f(location, value));
}

void Shader::setVector3Float(const std::string name, const float& x, const float& y, const float& z) const
{
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniform3f(location, x, y, z));
}

void Shader::setVector3Float(const std::string name, const float* values) const
{
    GLint location = GL_CALL(glGetUniformLocation(mProgram, name.c_str()));
    GL_CALL(glUniform3fv(location,1,values));
}

void Shader::checkShaderErrors(GLuint target, std::string type)
{
    int success = 0;
    char infoLog[1024] = { 0 };

    if (type == "COMPILE") {
        glGetShaderiv(target, GL_COMPILE_STATUS, &success);
        if (!success) {
            glGetShaderInfoLog(target, 1024, NULL, infoLog);
            std::cout << "ERROR: Shader compile error:  " << infoLog << std::endl;
        }
    } else if (type == "LINK") { 
        glGetProgramiv(target, GL_LINK_STATUS, &success);
        if (!success) {
            glGetProgramInfoLog(target, 1024, NULL, infoLog);
            std::cout << "ERROR: Shader link error :  " << infoLog << std::endl;
        }
    } else { 
        std::cout << "ERROR: Check shader errors Type is wrong" << std::endl;
    }
}

std::string Shader::readFile(const char* path)
{
    std::string content;
    std::ifstream fileStream(path, std::ios::in);
    std::string line = "";
    while (!fileStream.eof()) {
        getline(fileStream, line);
        content.append(line + "\n");
    }
    fileStream.close();
    return content;
}
