#include "EyerGLCustomComponent.hpp"
#include "EyerGLShader/Shader.hpp"

namespace Eyer
{
    EyerGLSingleTextureDraw::EyerGLSingleTextureDraw()
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


        textureDraw = new EyerGLDraw(GL_SHADER::SINGLE_TEXTURE_VERTEX_SHADER, GL_SHADER::SINGLE_TEXTURE_FRAGMENT_SHADER);
        textureDraw->Init();

        vao = new EyerGLVAO();

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        textureDraw->SetVAO(vao);
    }

    EyerGLSingleTextureDraw::~EyerGLSingleTextureDraw()
    {
        if(textureDraw != nullptr){
            delete textureDraw;
            textureDraw = nullptr;
        }
        if(vao != nullptr){
            delete vao;
            vao = nullptr;
        }
    }

    int EyerGLSingleTextureDraw::SetTexture(EyerGLTexture * _texture)
    {
        texture = _texture;

        return 0;
    }

    int EyerGLSingleTextureDraw::Draw()
    {
        if(texture != nullptr){
            textureDraw->PutTexture("imageTex",texture);
        }

        textureDraw->Draw();
        return 0;
    }
}