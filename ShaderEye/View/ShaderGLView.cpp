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

    if(cameraTexture != nullptr){
        delete cameraTexture;
        cameraTexture = nullptr;
    }

    if(cameraFrameComponent != nullptr){
        delete cameraFrameComponent;
        cameraFrameComponent = nullptr;
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

int ShaderGLView::SetShader(QString _vertex, QString _fragment)
{
    vertex = _vertex;
    fragment = _fragment;

    return 0;
}

void ShaderGLView::initializeGL()
{
    initializeOpenGLFunctions();

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

    rgb = new Eyer::EyerGLTexture(this);
    cameraTexture = new Eyer::EyerGLTexture(this);
    cameraFrameComponent = new ShaderEyeBGRACamera(this);
    shaderRender = new ShaderEyeRender(this);
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

    makeCurrent();

    glClear(GL_COLOR_BUFFER_BIT);

    Eyer::EyerGLFrameBuffer cameraFrameBuffer(cameraW, cameraH, cameraTexture, this);
    cameraFrameComponent->SetTexture(rgb);
    cameraFrameBuffer.AddComponent(cameraFrameComponent);
    cameraFrameBuffer.Draw();

    makeCurrent();



    Eyer::EyerGLFrameBuffer targetFrameBuffer(w * 2, h * 2, nullptr, this);
    shaderRender->SetShader(vertex.toStdString().c_str(), fragment.toStdString().c_str());
    shaderRender->SetCameraTexture(cameraTexture);
    targetFrameBuffer.AddComponent(shaderRender);
    targetFrameBuffer.Draw();

    makeCurrent();

    glFinish();
}
