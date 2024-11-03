#pragma once
#include "core.h"
#include <string>

class Texture {
public:
    Texture(const std::string& path, unsigned int unit);
    ~Texture();

    void bind();

private:
    int mWidth { 0 };
    int mHeight { 0 };
    int mUnit { 0 };
    GLuint mTexture { 0 };

};