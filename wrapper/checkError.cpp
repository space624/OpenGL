#include "checkError.h"

#include <assert.h>
#include <glad/glad.h>

#include <iostream>
#include <string>
void checkError() {
    GLenum errorCode = glGetError();

    if (errorCode != GL_NO_ERROR) {
        std::string error = "";
        switch (errorCode) {
        case GL_INVALID_ENUM:
            error = "INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            error = "INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            error = "INVALID_OPERATION";
            break;
        case GL_OUT_OF_MEMORY:
            error = "INVALID_OF_MEMORY";
            break;
        default:
            error = "UNKNOW";
            break;
        }
        std::cout << error << std::endl;
        assert(false);
    }
}