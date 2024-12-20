#include "glframework/core.h"

#include <iostream>
#include <string>

#include "wrapper/checkError.h"
#include "application/application.h"
#include "glframework/shader.h"
#include "glframework/texture.h"


GLuint VAO;
Shader* shader = nullptr;
Texture* texture = nullptr;
Texture* grassTexture = nullptr;
Texture* landTexture = nullptr;
Texture* noiseTexture = nullptr;

glm::mat4 transform(1.0);

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
    /*float positions [] = {
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

    float uvs [] = {
        0.0f,0.0f,
        1.0f,0.0f,
        0.5f,1.0f
    };

    unsigned int indices [] = {
        0,1,2,
        //2,1,3
    };
    */

    float positions [] = {
        -0.5f,-0.5f,0.0f,
        0.5f,-0.5f,0.0f,
        -0.5f,0.5f,0.0f,
        0.5f,0.5f,0.0f
    }; 

    float colors [] = {
        1.0f,0.0f,0.0f,
        0.0f,1.0f,0.0f,
        0.0f,0.0f,1.0f,
        0.5f,0.5f,0.5f
    };

    float uvs [] = {
        0.0f,0.0f,
        1.0f,0.0f,
        0.0f,1.0f,
        1.0f,1.0f
    };

    unsigned int indices [] = {
        0,1,2,
        2,1,3
    };
    

    GLuint POSVBO,COLORVBO, UVVBO;
    GLuint EBO;
    //GLuint VAO;

    glGenBuffers(1, &POSVBO);
    glBindBuffer(GL_ARRAY_BUFFER, POSVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    glGenBuffers(1, &COLORVBO);
    glBindBuffer(GL_ARRAY_BUFFER, COLORVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

    glGenBuffers(1, &UVVBO);
    glBindBuffer(GL_ARRAY_BUFFER, UVVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(uvs), uvs, GL_STATIC_DRAW);


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

    glBindBuffer(GL_ARRAY_BUFFER, UVVBO);
    glEnableVertexAttribArray(2);
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, (void*) 0);


    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);

    glBindVertexArray(0);

}

float ucolor[] = { 0.9, 0.3, 0.25 };

void prepareTexture() {
    //texture = new Texture("./assets/textures/goku.jpg", 0);
    grassTexture = new Texture("./assets/textures/grass.jpg", 0);
    landTexture = new Texture("./assets/textures/land.jpg", 1);
    noiseTexture = new Texture("./assets/textures/noise.jpg", 2);
}


//旋转
void doRotationTransform() {
    //构建一个旋转矩阵,绕着z轴旋转45度
    transform = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
}

//平移
void doTranslationTransform() {
    transform = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
}

//缩放
void doScaleTransform() {
    transform = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f, 0.5f, 1.0f));
}

void preTransform() {
    //先平移在旋转
    /* {
        transform = glm::translate(transform, glm::vec3(0.6f, 0.0f, 0.0f));
    } */

    //先旋转再平移
    /* {
        transform = glm::rotate(transform, glm::radians(45.0f), glm::vec3(0.0f, 0.0f, 0.0f));
    } */

    //先做一次缩放, 再叠加平移
    transform = glm::scale(transform, glm::vec3(1.0f, 1.0f, 1.0f));
}

//连续变换
void doTransform() {
    //glm::mat4 rotateMat = glm::rotate(glm::mat4(1.0f), glm::radians(45.0f), glm::vec3(0.0, 0.0, 1.0));
    //glm::mat4 translateMat = glm::translate(glm::mat4(1.0f), glm::vec3(0.5f, 0.0f, 0.0f));
    ////transform = glm::translate(rotateMat, glm::vec3(0.5f, 0.0f, 0.0f));
    //transform = translateMat * rotateMat;

    //旋转
    /* {
        float angle = 1.0f;
        transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    }*/

    //先平移在旋转
    /* {
        float angle = 1.0f;
        **** transform = glm::translate(transform, glm::vec3(0.002f, 0.0f, 0.0f));
        transform = glm::rotate(transform, glm::radians(angle), glm::vec3(0.0f, 0.0f, 1.0f));
    } */

    //先旋转再平移
    //preTransform做一次旋转然后在做平移
    /* {
        transform = glm::translate(transform, glm::vec3(0.01f, 0.0f, 0.0f));
    } */

    //先做一次缩放,再叠加平移
    //preTransform做一次缩放
    transform = glm::translate(transform, glm::vec3(0.01f, 0.0f, 0.0f));

}

float angle = 0.0f;
void doRotaion() {
    angle += 2.0f;
    transform = glm::rotate(glm::mat4(1.0f), glm::radians(angle), glm::vec3(0.0, 0.0, 1.0));
}

void render() {
    GL_CALL(glClear(GL_COLOR_BUFFER_BIT));

    //绑定当前的program
    shader->begin(); 
    shader->setUniformFloat("time", glfwGetTime());
    //shader->setUniformFloat("speed", glfwGetTime());
    shader->setInt("sampler", 0);
    //doRotaion();
    shader->setMatrix4x4("transform", transform);

    shader->setInt("grassSampler", 0);
    shader->setInt("landSampler", 1);
    shader->setInt("noiseSampler", 2);

    shader->setUniformFloat("width", landTexture->getWidth());
    shader->setUniformFloat("height", landTexture->getWidth());
     
    //shader->setVector3Float("uColor", ucolor);
    //shader->setVector3Float("uColor", 0.3, 0.4, 0.5);

    //绑定当前的VAO
    glBindVertexArray(VAO);
    //绘制
    //glDrawArrays(GL_TRIANGLES, 0, 6);
    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
    // glDrawElements(GL_TRIANGLES, 3, GL_UNSIGNED_INT, (void*)(sizeof(int)*3));
    glBindVertexArray(0);
    shader->end();

}

int main(void) {
    
    //向量
    glm::vec2 v0(0);
    glm::vec3 v1(0);
    glm::vec4 v2(0);

    glm::vec4 vadd = v2 + glm::vec4(0);
    auto mul = vadd * v2;   //对应元素相乘, 放到对应位置

    //点乘
    auto dotRes = glm::dot(vadd, v2);
    //叉乘   只能给三维使用
    glm::vec3 vt0, vt1;
    auto crossRes = glm::cross(vt0, vt1);

    //矩阵
    glm::mat4 m0(1.0);
    glm::mat4 m1 = glm::identity<glm::mat4>();
    glm::mat2 mm2(1.0);
    glm::mat3 mm3(1.0);
    glm::mat2x3 mm4(1.0);

    std::cout << glm::to_string(mm4) << std::endl;

    auto madd = m0 + m1;
    auto mmulti = m0 * m1;
    auto res = m0 * v2;

    //transpose 转置矩阵
    auto transMat = glm::transpose(madd);

    //inverse 逆矩阵
    auto inverseMat = glm::inverse(madd);

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
    prepareTexture();

    //doRotationTransform();
    //doTranslationTransform();
    //doScaleTransform();
    //doTransform();
    preTransform();
    while (app->update()) {
        doTransform();
        render();
        
    }

    app->destroy();
    //delete texture;
    delete grassTexture;
    delete landTexture;

    return 0;
}