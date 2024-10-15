#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include <iostream>
#include <string>

#include "wrapper/checkError.h"
#include "application/application.h"

GLuint VAO, program;
void frameBufferSizeCallBack(GLFWwindow* window, int width, int height) {
    glViewport(0, 0, width, height);
}

void keyCallBack(int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_W)
        std::cout << "按下W: " << key << std::endl;
}

void onResize(int width, int height) {
    GL_CALL(glViewport(0, 0, width, height));
}

void prepareVBO() {
    // 创建VBO
    GLuint VBO = 0;
    GL_CALL(glGenBuffers(1, &VBO));

    GLuint VBOARR [] = { 0,0,0 };
    GL_CALL(glGenBuffers(3, VBOARR));

    // 分配显存

    // 销毁
    GL_CALL(glDeleteBuffers(1, &VBO));
    GL_CALL(glDeleteBuffers(3, VBOARR));
}

void prepare() {

    float vertieces [] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f
    };

    float colors [] = {
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f
    };

    GLuint VBO = 0;
    GL_CALL(glGenBuffers(1, &VBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));

    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(vertieces), vertieces, GL_STATIC_DRAW));

    GL_CALL(glDeleteBuffers(1, &VBO));

}

//void prepareSingleBuffer() {
//    float positions [] = {
//        -0.5f,-0.5f,0.0f,
//        0.5f,-0.5f,0.0f,
//        0.0f,0.5f,0.0f
//    };
//
//    float colors [] = {
//        1.0f,0.0f,0.0f,
//        0.0f,1.0f,0.0f,
//        0.0f,0.0f,1.0f
//    };
//
//    GLuint posVBO = 0, colorVBO = 0;
//
//    GL_CALL(glGenBuffers(1, &posVBO));
//    GL_CALL(glGenBuffers(1, &colorVBO));
//
//    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, posVBO));
//    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
//
//    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, colorVBO));
//    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW));
//
//}

void prepareDoubleBuffer() {
    float positions [] = {
        -0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
        0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
        0.0f,0.5f,0.0f, 0.0f,0.0f,1.0f
    };

    GLuint VBO = 0;
    GL_CALL(glGenBuffers(1, &VBO));
    GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, VBO));

    GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW));
}

void prepareSingleBuffer() {
    float positions [] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f
    };

    float colors [] = {
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f
    };

    GLuint posVBO, colorVBO;
    glGenBuffers(1, &posVBO);
    glGenBuffers(2, &colorVBO);

    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);

    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    GLuint VAO;
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    //绑定posVBO
    glBindBuffer(GL_ARRAY_BUFFER, posVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    //绑定colorVBO
    glBindBuffer(GL_ARRAY_BUFFER, colorVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    glBindVertexArray(0);
}

void prepareInterleavedBuffer() {
    float positions [] = {
        -0.5f,-0.5f,0.0f,1.0f,0.0f,0.0f,
        0.5f,-0.5f,0.0f, 0.0f,1.0f,0.0f,
        0.0f,0.5f,0.0f, 0.0f,0.0f,1.0f
    };

    //GLuint VAO, VBO;
    GLuint  VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) ( 3 * sizeof(float) ));

    glBindVertexArray(0);
    glBindVertexArray(0);

}

void prepareShader() {
    const char* vertexShaderSource =
        "#version 460 core\n"
        "layout (location = 0) in vec3 aPos;\n"
        "void main()\n"
        "{\n"
        "   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
        "}\0";
    const char* fragmentShaderSource =
        "#version 330 core\n"
        "out vec4 FragColor;\n"
        "void main()\n"
        "{\n"
        "   FragColor = vec4(1.0f, 0.5f, 0.2f, 1.0f);\n"
        "}\n\0";

    //创建Shader程序
    //VS  FS
    GLuint vertex, fragment;
    vertex = glCreateShader(GL_VERTEX_SHADER);
    fragment = glCreateShader(GL_FRAGMENT_SHADER);

    //输入Shader程序代码
    glShaderSource(vertex, 1, &vertexShaderSource, NULL);
    glShaderSource(fragment, 1, &fragmentShaderSource, NULL);

    //Shader代码编译
    glCompileShader(vertex);
    glCompileShader(fragment);

    //编译检查结果
    int success = 0;
    glGetShaderiv(vertex, GL_COMPILE_STATUS, &success);
    if (!success) { 
        char infoLog[1024] = {0};
        glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
        std::cout << "ERROR: Shader compile error --vertex :  " << infoLog << std::endl;
    }

    glGetShaderiv(fragment, GL_COMPILE_STATUS, &success);
    if (!success) {
        char infoLog[1024] = {0};
        glGetShaderInfoLog(vertex, 1024, NULL, infoLog);
        std::cout << "ERROR: Shader compile error --fragment :  " << infoLog << std::endl;
    }

    //创建Program
    //GLuint program = glCreateProgram();

    //编译好的结果放入Program
    glAttachShader(program, vertex);
    glAttachShader(program, fragment);

    //链接
    glLinkProgram(program);
    //检查链接是否错误
    glGetProgramiv(program, GL_LINK_STATUS, &success);
    if (!success) {
        char infoLog[1024] = { 0 };
        glGetProgramInfoLog(program, 1024, NULL, infoLog);
        std::cout << "ERROR: Shader link error --program :  " << infoLog << std::endl;
    }

    glDeleteShader(vertex);
    glDeleteShader(fragment);

}

void prepareVAOForGLTriangles() {
    float positions [] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f,
        0.5f,0.5f,0.0f,
        0.8f,0.8f,0.0f,
        0.8f,0.0f,0.0f
    };

    //GLuint VAO, VBO;
    GLuint  VBO;
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) 0);

    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*) ( 3 * sizeof(float) ));

    glBindVertexArray(0);
    glBindVertexArray(0);

}

void render() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    //绑定当前的program
    glUseProgram(program);
    //绑定当前的VAO
    glBindVertexArray(VAO);
    //绘制
    glDrawArrays(GL_TRIANGLES, 0, 6);
}

int main(void) {
    
    if (!app->init()) { 
        return -1;
    }
    
    app->setResizeCallBack(onResize);
    app->setKeyCallBack(keyCallBack);
    // 窗体更改
    //glfwSetFramebufferSizeCallback(window, frameBufferSizeCallBack);

    // 键盘监听
    //glfwSetKeyCallback(window, keyCallBack);

    glViewport(0, 0, 800, 600);
    glClearColor(0.2f, 0.3f, 0.3f, 1.0f);

    //prepareShader();
    //prepareInterleavedBuffer();
    prepareVAOForGLTriangles();
    while (app->update()) {
        
        render();
        
    }

    app->destroy();
    
    return 0;
}