#ifndef	SHADER_EYE_GL_VIEW_H
#define	SHADER_EYE_GL_VIEW_H

#include <QWidget>
#include <QOpenGLWidget>
#include <QOpenGLFunctions_3_3_Core>
#include <QEvent>
#include <QWheelEvent>
#include <QVideoFrame>

#include "EyerGL/EyerGL.hpp"
#include "EyerGLShader/Shader.hpp"
#include "EyerGL/EyerGLCustomComponent/EyerGLCustomComponent.hpp"

#include "EyerGLShader/Shader.hpp"
#include <QDebug>
#include "Component/ShaderEyeComponent.hpp"

class GLView : public QOpenGLWidget , protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit GLView(QWidget * parent = 0);
    ~GLView();

    int SetCameraFrame(const uchar *data, QVideoFrame::PixelFormat format, int linesize, int width, int height);
    int SetCameraHW(int w, int h);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    Eyer::EyerGLTexture * rgb = nullptr;
    Eyer::EyerGLDraw * glDraw = nullptr;
    Eyer::EyerGLVAO * vao = nullptr;

    int cameraW = 0;
    int cameraH = 0;

    int w = 0;
    int h = 0;
};


class CameraGLView : public QOpenGLWidget , protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit CameraGLView(QWidget * parent = 0);
    ~CameraGLView();

    int SetCameraFrame(const uchar *data, QVideoFrame::PixelFormat format, int linesize, int width, int height);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    Eyer::EyerGLTexture * rgb = nullptr;
    Eyer::EyerGLDraw * glDraw = nullptr;
    Eyer::EyerGLVAO * vao = nullptr;

    int cameraW = 0;
    int cameraH = 0;

    int w = 0;
    int h = 0;
};




class ShaderGLView : public QOpenGLWidget , protected QOpenGLFunctions_3_3_Core
{
    Q_OBJECT
public:
    explicit ShaderGLView(QWidget * parent = 0);
    ~ShaderGLView();

    int SetShader(QString _vertex, QString _fragment);
    int SetCameraFrame(const uchar *data, QVideoFrame::PixelFormat format, int linesize, int width, int height);

protected:
    void initializeGL();
    void resizeGL(int w, int h);
    void paintGL();

private:
    Eyer::EyerGLTexture * rgb = nullptr;
    Eyer::EyerGLTexture * cameraTexture = nullptr;

    ShaderEyeBGRACamera * cameraFrameComponent = nullptr;
    ShaderEyeRender * shaderRender = nullptr;

    int cameraW = 0;
    int cameraH = 0;

    int w = 0;
    int h = 0;

    QString vertex;
    QString fragment;
};

#endif
