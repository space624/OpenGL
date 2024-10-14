#include "application.h"

#include <GLFW/glfw3.h>

Application* Application::instance_ = nullptr;

Application::Application()
{
}

Application::~Application()
{
}

Application* Application::getInstance()
{
    if (!instance_)
        instance_ = new Application;

    return instance_;
}

bool Application::init(const int& width, const int& height)
{
    width_ = width;
    height_ = height;
    glfwInit();
    // ���ð汾��
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // ��������
    window_ = glfwCreateWindow(width, height, "OpenGLStudy", NULL, NULL);
    if (!window_) { 
        return false;
    }
    // �󶨴���
    glfwMakeContextCurrent(window_);

    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        std::cout << "Failed to initialize CLAD" << std::endl;
        return false;
    }

    glfwSetFramebufferSizeCallback(window_, frameBufferSizeCallback);
    glfwSetKeyCallback(window_, KeyCallback);

    glfwSetWindowUserPointer(window_, this);

    return true;
}

bool Application::update()
{
    if (glfwWindowShouldClose(window_)) {
        return false;
    }

    glfwPollEvents();
    // �л�˫����
    glfwSwapBuffers(window_);
}

void Application::destroy()
{
    glfwTerminate();
}

void Application::frameBufferSizeCallback(GLFWwindow* window, const int width, const int height)
{
    Application* self = (Application*) glfwGetWindowUserPointer(window);
    if(self->resizeCallBack_)
        self->resizeCallBack_(width, height);
}

void Application::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    std::cout << "���̰���" << std::endl;
    Application* self = (Application*) glfwGetWindowUserPointer(window);
    if(self->keyCallBack_)
        self->keyCallBack_(key, scancode, action, mods);
}
