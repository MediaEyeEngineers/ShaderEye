#include "GLView.hpp"
#include "EyerGLShader/Shader.hpp"

GLView::GLView(QWidget * parent) : QOpenGLWidget(parent)
{

}

GLView::~GLView()
{
    if(rgb != nullptr){
        delete rgb;
        rgb = nullptr;
    }
}

int GLView::SetCameraHW(int w, int h)
{
    cameraW = w;
    cameraH = h;
    return 0;
}

int GLView::SetCameraFrame(const uchar * data, qint64 startTime)
{
    if(rgb != nullptr){
        // rgb->SetDataRGBChannel((unsigned char *)data, cameraW, cameraH);
        rgb->SetDataRGBAChannel((unsigned char *)data, cameraW, cameraH);
    }
    update();
}

void GLView::initializeGL()
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

void GLView::resizeGL(int _w, int _h)
{
    w = _w;
    h = _h;
}

void GLView::paintGL()
{
    if(rgb == nullptr){
        return;
    }

    glClear(GL_COLOR_BUFFER_BIT);

    Eyer::EyerMat4x4 mat;

    glDraw->PutMatrix4fv("mvp", mat);
    glDraw->PutTexture("imageTex", rgb, 0);

    glDraw->Draw();
}
