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
    Eyer::EyerGLFrameBuffer cameraFrameBuffer(cameraW, cameraH, nullptr, this);

    ShaderEyeBGRACamera cameraFrameComponent(this);
    cameraFrameComponent.SetTexture(rgb);
    cameraFrameComponent.Draw();

    cameraFrameBuffer.AddComponent(&cameraFrameComponent);
    cameraFrameBuffer.Draw();


    // Eyer::EyerGLFrameBuffer targetFrameBuffer(w, h, nullptr, this);

    /*



    Eyer::EyerMat4x4 mat;
    glDraw->PutMatrix4fv("mvp", mat);
    glDraw->PutTexture("imageTex", rgb, 0);

    glDraw->Draw();
    */

    glFinish();
}
