#include "GLView.hpp"
#include "EyerGLShader/Shader.hpp"
#include <QDebug>
#include "Component/ShaderEyeComponent.hpp"

ShaderGLView::ShaderGLView(QWidget * parent) : QOpenGLWidget(parent)
{

}

ShaderGLView::~ShaderGLView()
{
    if(rgb != nullptr){
        delete rgb;
        rgb = nullptr;
    }
}

int ShaderGLView::SetCameraFrame(const uchar *data, QVideoFrame::PixelFormat format, int linesize, int width, int height)
{
    cameraW = width;
    cameraH = height;
    if(rgb != nullptr){
        rgb->SetDataRGBAChannel((unsigned char *)data, width, height);
    }
    update();
}

void ShaderGLView::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    rgb = new Eyer::EyerGLTexture(this);


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

    glDraw = new Eyer::EyerGLDraw(Eyer::EYER_GL_SHADER::MVP_TEXTURE_VERTEX_SHADER, Eyer::EYER_GL_SHADER::MVP_TEXTURE_FRAGMENT_SHADER, this);
    glDraw->Init();

    vao = new Eyer::EyerGLVAO(this);

    vao->AddVBO(vertex, sizeof(vertex), 0);
    vao->AddVBO(coor, sizeof(coor), 1);
    vao->SetEBO(vertexIndex, sizeof(vertexIndex));

    glDraw->SetVAO(vao);
}

void ShaderGLView::resizeGL(int _w, int _h)
{
    w = _w;
    h = _h;
}

void ShaderGLView::paintGL()
{
    if(rgb == nullptr){
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    Eyer::EyerGLTexture cameraTexture(this);
    Eyer::EyerGLFrameBuffer cameraFrameBuffer(cameraW, cameraH, &cameraTexture, this);

    ShaderEyeBGRACamera cameraFrameComponent(this);
    cameraFrameComponent.SetTexture(rgb);

    cameraFrameBuffer.AddComponent(&cameraFrameComponent);
    cameraFrameBuffer.Draw();


    // Eyer::EyerGLFrameBuffer targetFrameBuffer(w, h, nullptr, this);

    ShaderEyeRender shaderRender(this);


    char * TEST_TEXTURE_VERTEX_SHADER = (char *)SHADER(
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec3 coor;

        out vec3 outCoor;

        void main(){
            outCoor = coor;
            gl_Position = vec4(pos, 1.0);
        }
    );

    char * TEST_TEXTURE_FRAGMENT_SHADER = (char *)SHADER(
        out vec4 color;
        uniform sampler2D cameraTex;
        in vec3 outCoor;
        void main(){
            vec2 TexCoords = vec2(1.0 - outCoor.x, 1.0 - outCoor.y);
            vec4 color_t = texture(cameraTex, TexCoords);

            color.x = color_t.z;
            color.y = color_t.y;
            color.z = color_t.x;
            color.w = color_t.w;
        }
    );
    shaderRender.SetShader(TEST_TEXTURE_VERTEX_SHADER, TEST_TEXTURE_FRAGMENT_SHADER);
    shaderRender.SetCameraTexture(&cameraTexture);
    shaderRender.Draw();

    // targetFrameBuffer.AddComponent(&shaderRender);
    // targetFrameBuffer.Draw();

    glFinish();
}
