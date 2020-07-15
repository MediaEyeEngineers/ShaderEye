#ifndef	SHADER_EYE_GL_VIEW_H
#define	SHADER_EYE_GL_VIEW_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QEvent>
#include <QWheelEvent>

#include "EyerGL/EyerGL.hpp"
#include "EyerGLShader/Shader.hpp"
#include "EyerGL/EyerGLCustomComponent/EyerGLCustomComponent.hpp"

class GLView : public QOpenGLWidget , protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit GLView(QWidget * parent = 0);
    ~GLView();

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    Eyer::EyerGLJulia * julia = nullptr;
};

#endif
