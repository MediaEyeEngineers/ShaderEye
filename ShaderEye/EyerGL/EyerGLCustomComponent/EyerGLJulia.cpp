#include "EyerGLCustomComponent.hpp"
#include "EyerGLShader/Shader.hpp"

namespace Eyer
{
    EyerGLJulia::EyerGLJulia(EyerGLContext * _ctx)
    {
        ctx = _ctx;
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

        textureDraw = new EyerGLDraw(EYER_GL_SHADER::JULIA_VERTEX_SHADER, EYER_GL_SHADER::JULIA_FRAGMENT_SHADER, ctx);

        Eyer::EyerGLShaderError vertexShaderError;
        Eyer::EyerGLShaderError fragmentShaderError;
        Eyer::EyerGLProgramError programError;
        textureDraw->Init(vertexShaderError, fragmentShaderError, programError);

        vao = new EyerGLVAO(ctx);

        vao->AddVBO(vertex, sizeof(vertex), 0);
        vao->AddVBO(coor, sizeof(coor), 1);
        vao->SetEBO(vertexIndex, sizeof(vertexIndex));

        textureDraw->SetVAO(vao);

        startTime = 0;
    }

    EyerGLJulia::~EyerGLJulia()
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

    int EyerGLJulia::SetWH(int _w, int _h)
    {
        w = _w;
        h = _h;
        return 0;
    }

    int EyerGLJulia::Draw()
    {
        startTime += 0.01f;
        textureDraw->PutUniform1f("width", w);
        textureDraw->PutUniform1f("height", h);
        textureDraw->PutUniform1f("iTime", startTime * 1.0f);
        textureDraw->Draw();
        return 0;
    }
}
