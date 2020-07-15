#include "EyerGLCustomComponent.hpp"
#include "EyerGLShader/Shader.hpp"

namespace Eyer
{
    EyerGLYUV2TextureComponent::EyerGLYUV2TextureComponent()
    {
        float vertex[] = {
                1.0, 1.0, 0.0,
                1.0, -1.0, 0.0,
                -1.0, -1.0, 0.0,
                -1.0, 1.0, 0.0
        };
        float coor[] = {
                1.0, 1.0, 0.0,
                1.0, 0.0, 0.0,
                0.0, 0.0, 0.0,
                0.0, 1.0, 0.0
        };
        unsigned int vertexIndex[] = {
                0, 1, 2,
                0, 2, 3
        };

        yuv2texture = new EyerGLDraw(GL_SHADER::YUV_2_TEXTURE_VERTEX_SHADER, GL_SHADER::YUV_2_TEXTURE_FRAGMENT_SHADER);
        yuv2texture->Init();

        vao = new EyerGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        yuv2texture->SetVAO(vao);
    }

    EyerGLYUV2TextureComponent::~EyerGLYUV2TextureComponent()
    {
        if(yuv2texture != nullptr){
            delete yuv2texture;
            yuv2texture = nullptr;
        }
        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }
    }


    int EyerGLYUV2TextureComponent::SetYTexture(EyerGLTexture * _yTex)
    {
        yTex = _yTex;
        return 0;
    }

    int EyerGLYUV2TextureComponent::SetUTexture(EyerGLTexture * _uTex)
    {
        uTex = _uTex;
        return 0;
    }

    int EyerGLYUV2TextureComponent::SetVTexture(EyerGLTexture * _vTex)
    {
        vTex = _vTex;
        return 0;
    }

    int EyerGLYUV2TextureComponent::Draw()
    {
        if(yTex != nullptr){
            yuv2texture->PutTexture("y",yTex, 0);
        }
        if(uTex != nullptr){
            yuv2texture->PutTexture("u",uTex, 1);
        }
        if(vTex != nullptr){
            yuv2texture->PutTexture("v",vTex, 2);
        }

        yuv2texture->PutUniform1i("reverseY", reverseY);
        yuv2texture->PutUniform1i("colorRange", (int)colorRange);

        yuv2texture->Draw();
        return 0;
    }

    int EyerGLYUV2TextureComponent::SetReverseY(int _reverseY)
    {
        reverseY = _reverseY;
        return 0;
    }

    int EyerGLYUV2TextureComponent::SetColoRange(EyerGLYUV2TextureComponentColorRange _colorRange)
    {
        colorRange = _colorRange;
        return 0;
    }
}