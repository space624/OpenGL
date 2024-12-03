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
    // glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mWidth, mHeight, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //int width = mWidth;
    //int height = mHeight;
    //for (int level = 0; true; ++level) { 
    //    //�ѵ�ǰ��mipmap��Ӧ�����ݷ���GPU
    //    glTexImage2D(GL_TEXTURE_2D, level, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);

    //    //�Ƿ��˳�ѭ��
    //    if (width == 1 && height == 1) { 
    //        break;
    //    }

    //    //������һ��ѭ���Ŀ�Ⱥ͸߶�
    //    width = width > 1 ? width / 2 : 1;
    //    height = height > 1 ? height / 2 : 1;

    //}

    //�ͷ�����
    stbi_image_free(data);

    //����mipmap
    glGenerateMipmap(GL_TEXTURE_2D);

    //����������˷�ʽ
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    //glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST_MIPMAP_LINEAR);

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

