#include "ShaderEyeComponent.hpp"
#include "EyerGLShader/Shader.hpp"

ShaderEyeBGRACamera::ShaderEyeBGRACamera(EyerGLContext * _ctx)
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

    char * BGRA_TEXTURE_VERTEX_SHADER = (char *)SHADER(
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec3 coor;

        out vec3 outCoor;

        void main(){
            outCoor = coor;
            gl_Position = vec4(pos, 1.0);
        }
    );

    char * BGRA_TEXTURE_FRAGMENT_SHADER = (char *)SHADER(
        out vec4 color;
        uniform sampler2D imageTex;
        in vec3 outCoor;
        void main(){
            vec2 TexCoords = vec2(1.0 - outCoor.x, 1.0 - outCoor.y);
            vec4 color_t = texture(imageTex, TexCoords);

            color.x = color_t.z;
            color.y = color_t.y;
            color.z = color_t.x;
            color.w = color_t.w;
        }
    );

    bgra = new Eyer::EyerGLDraw(BGRA_TEXTURE_VERTEX_SHADER, BGRA_TEXTURE_FRAGMENT_SHADER, ctx);

    Eyer::EyerGLShaderError vertexShaderError;
    Eyer::EyerGLShaderError fragmentShaderError;
    Eyer::EyerGLProgramError programError;
    bgra->Init(vertexShaderError, fragmentShaderError, programError);

    vao = new Eyer::EyerGLVAO(ctx);

    vao->AddVBO(vertex, sizeof(vertex), 0);
    vao->AddVBO(coor, sizeof(coor), 1);
    vao->SetEBO(vertexIndex, sizeof(vertexIndex));

    bgra->SetVAO(vao);
}

ShaderEyeBGRACamera::~ShaderEyeBGRACamera()
{
    if(bgra != nullptr){
        delete bgra;
        bgra = nullptr;
    }

    if(vao != nullptr){
        delete vao;
        vao = nullptr;
    }
}

int ShaderEyeBGRACamera::SetTexture(Eyer::EyerGLTexture * _frameTexture)
{
    frameTexture = _frameTexture;
    return 0;
}

int ShaderEyeBGRACamera::Draw()
{
    if(frameTexture != nullptr){
        bgra->PutTexture("imageTex", frameTexture, 0);
        bgra->Draw();
    }
    return 0;
}
