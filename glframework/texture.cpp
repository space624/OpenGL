#include "texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include "../application/stb_image.h"

Texture::Texture(const std::string& path, unsigned int unit)
{
    mUnit = unit;
    //��ȡͼƬ
    int  channels;
    //--��תY��
    stbi_set_flip_vertically_on_load(true);
    unsigned char* data = stbi_load(path.c_str(), &mWidth, &mHeight, &channels, STBI_rgb_alpha);

    //��������,���Ԫ��
    glGenTextures(1, &mTexture);

    //��������Ԫ
    glActiveTexture(GL_TEXTURE0 + mUnit);

    //���������
    glBindTexture(GL_TEXTURE_2D, mTexture);

    //������������,�����Դ�
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //�ͷ�����
    stbi_image_free(data);

    //����������˷�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);

    //��������İ�����ʽ
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

