#pragma once

#include "core.h"
#include <string>
class Shader {
public:
    Shader(const char* vertesPath, const char* fragmentPath);
    ~Shader();

    void begin();
    void end();

private:
    void checkShaderErrors(GLuint target, std::string type);
    std::string readFile(const char* path);
private:
    GLuint mProgram { 0 };
};