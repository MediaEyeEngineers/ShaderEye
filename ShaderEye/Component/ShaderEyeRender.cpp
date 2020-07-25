#include "ShaderEyeComponent.hpp"
#include "EyerGLShader/Shader.hpp"

ShaderEyeRender::ShaderEyeRender(EyerGLContext * _ctx)
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

    // bgra = new Eyer::EyerGLDraw(BGRA_TEXTURE_VERTEX_SHADER, BGRA_TEXTURE_FRAGMENT_SHADER, ctx);
    // bgra->Init();

    vao = new Eyer::EyerGLVAO(ctx);

    vao->AddVBO(vertex, sizeof(vertex), 0);
    vao->AddVBO(coor, sizeof(coor), 1);
    vao->SetEBO(vertexIndex, sizeof(vertexIndex));

    // bgra->SetVAO(vao);
}

ShaderEyeRender::~ShaderEyeRender()
{
    if(draw != nullptr){
        delete draw;
        draw = nullptr;
    }

    if(vao != nullptr){
        delete vao;
        vao = nullptr;
    }
}

int ShaderEyeRender::SetShader(const char * vertex, const char * fragment, Eyer::EyerGLShaderError & vertexShaderError, Eyer::EyerGLShaderError & fragmentShaderError, Eyer::EyerGLProgramError & programError)
{
    if(draw != nullptr){
        delete draw;
        draw = nullptr;
    }

    draw = new Eyer::EyerGLDraw(vertex, fragment, ctx);

    draw->Init(vertexShaderError, fragmentShaderError, programError);

    draw->SetVAO(vao);

    return 0;
}

int ShaderEyeRender::SetCameraTexture(Eyer::EyerGLTexture * _cameraTexture)
{
    cameraTexture = _cameraTexture;
    return 0;
}

int ShaderEyeRender::Draw()
{
    if(cameraTexture != nullptr){
        if(draw != nullptr){
            draw->PutTexture("cameraTex", cameraTexture, 0);
            draw->Draw();
        }
    }
    return 0;
}
