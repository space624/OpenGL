#include "glframework/core.h"

#include <iostream>
#include <string>

#include "wrapper/checkError.h"
#include "application/application.h"
#include "glframework/shader.h"

GLuint VAO;
Shader* shader = nullptr;
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
    shader = new Shader("./assets/shaders/vertex.glsl", "./assets/shaders/fragment.glsl");
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

void prepareVAO() {
    float positions [] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        0.0f,0.5f,0.0f,
        0.5f,0.5f,0.0f
    };

    float colors [] = {
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f
    };

    unsigned int indices [] = {
        0,1,2,
        //2,1,3
    };

    GLuint POSVBO,COLORVBO;
    GLuint EBO;
    //GLuint VAO;

    glGenBuffers(1, &POSVBO);
    glBindBuffer(GL_ARRAY_BUFFER, POSVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glGenBuffers(1, &COLORVBO);
    glBindBuffer(GL_ARRAY_BUFFER, COLORVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);


    glGenBuffers(1, &EBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, POSVBO);
    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);

    //add color data
    glBindBuffer(GL_ARRAY_BUFFER, COLORVBO);
    glEnableVertexAttribArray(1);
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, (void*) 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBindVertexArray(0);

}

void render() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    //绑定当前的program
    shader->begin();

    //绑定当前的VAO
    glBindVertexArray(VAO);
    //绘制
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(int)*3));
    glBindVertexArray(0);
    shader->end();

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

    prepareShader();
    //prepareInterleavedBuffer();
    //prepareVAOForGLTriangles();
    prepareVAO();
    while (app->update()) {
        
        render();
        
    }

    app->destroy();
    
    return 0;
}