#include "GLView.hpp"

GLView::GLView(QWidget * parent) : QOpenGLWidget(parent)
{

}

GLView::~GLView()
{
    if(julia != nullptr){
        delete julia;
        julia = nullptr;
    }
}

void GLView::initializeGL()
{
    initializeOpenGLFunctions();

    julia = new Eyer::EyerGLJulia(this);

    glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
}

void GLView::resizeGL(int w, int h)
{
    julia->SetWH(w, h);
}

void GLView::paintGL()
{
    julia->Draw();

    update();
}
