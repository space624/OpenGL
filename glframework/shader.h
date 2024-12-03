#pragma once

#include "core.h"
#include <string>
class Shader {
public:
    Shader(const char* vertesPath, const char* fragmentPath);
    ~Shader();

    void begin() const;
    void end() const;

    void setUniformFloat(const std::string name, const float& value) const;
    void setVector3Float(const std::string name, const float& x, const float& y, const float& z) const;
    void setVector3Float(const std::string name, const float* values) const;
    void setInt(const std::string& name, int value) const;

    void setMatrix4x4(const std::string name, const glm::mat4 value) const;

    GLuint getProgram() const { return mProgram; }
private:
    void checkShaderErrors(GLuint target, std::string type);
    std::string readFile(const char* path);
private:
    GLuint mProgram { 0 };
};