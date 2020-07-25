#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "CameraController.h"
#include "CompileInfoWindow.h"
#include "View/GLView.hpp"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    // btn click event
    void mainCameraOpenClick();
    void mainRenderCompileClick();
    // DlgSettingCamera signals
    void readFrame(const uchar *data, QVideoFrame::PixelFormat format, int linesize, int width, int height);

private:
    Ui::MainWindow *ui;
    CameraController *cameraControl = nullptr;
    CompileInfoWindow *compileDiglogControl = nullptr;
    
    CameraGLView * glViewCapture = nullptr;
    ShaderGLView * glViewRender = nullptr;
};
#endif // MAINWINDOW_H
