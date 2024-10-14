#pragma once

#include <glad/glad.h>
#include <iostream>

#define app Application::getInstance()

class GLFWwindow;

using ResizeCallBack = void( * )( int, int );
using KeyCallBack = void( * )( int, int, int, int );


class Application {
public:
    ~Application();
    static Application* getInstance();

    bool init(const int& width = 800, const int& height = 600);
    bool update();
    void destroy();


    void setResizeCallBack(ResizeCallBack callback) { resizeCallBack_ = callback; }
    void setKeyCallBack(KeyCallBack callback) { keyCallBack_ = callback; }


    uint32_t getWidth() const { return width_; }
    uint32_t getHeight() const { return height_; }

private:
    static void frameBufferSizeCallback(GLFWwindow* window, const int width, const int height);
    static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

private:
    Application();

    uint32_t width_ { 0 };
    uint32_t height_ { 0 };
    GLFWwindow* window_ = nullptr;

    ResizeCallBack resizeCallBack_;
    KeyCallBack keyCallBack_;

    static Application* instance_;
};