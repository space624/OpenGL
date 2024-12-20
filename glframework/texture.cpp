#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"

Texture::Texture(const std::string& path, unsigned int unit)
{
    mUnit = unit;
    //读取图片
    int  channels;
    //--反转Y轴
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);

    //生成纹理,激活单元绑定
    glGenTextures(1, &mTexture);

    //激活纹理单元
    glActiveTexture(GL_TEXTURE0 + mUnit);

    //绑定纹理对象
    glBindTexture(GL_TEXTURE_2D, mTexture);

    //传输纹理数据,开辟显存
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //int width = mWidth;
    //int height = mHeight;
    //for (int level = 0; true; ++level) { 
    //    //把当前的mipmap对应的数据发往GPU
    //    glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //    //是否退出循环
    //    if (width == 1 && height == 1) { 
    //        break;
    //    }

    //    //计算下一次循环的宽度和高度
    //    width = width > 1 ? width / 2 : 1;
    //    height = height > 1 ? height / 2 : 1;

    //}

    //释放数据
    stbi_image_free(data);

    //生成mipmap
    glGenerateMipmap(GL_TEXTURE_2D);

    //设置纹理过滤方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

    //设置纹理的包裹方式
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);  //u
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);  //v
}

Texture::~Texture()
{
    if (mTexture != 0) { 
        glDeleteTextures(1, &mTexture);
    }
}

void Texture::bind()
{
    glActiveTexture(GL_TEXTURE0 + mUnit);
    glBindTexture(GL_TEXTURE_2D, mTexture);
}

