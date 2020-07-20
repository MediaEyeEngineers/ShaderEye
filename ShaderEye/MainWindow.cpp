#include "MainWindow.h"
#include "ui_MainWindow.h"

/**
 * @date 2020/07/19
 * @author changyanlong github.com/numberwolf q531365872
 */
#include "View/GLView.hpp"
#include "CommonSetting.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(TITLE_MAIN_WIN);

    GLView * glViewRender = new GLView(this);
    glViewRender->setGeometry(0, 0, 400, 400);
    ui->RenderLayout->addWidget(glViewRender);

    GLView * glViewCapture = new GLView(this);
    ui->CaptureLayout->addWidget(glViewCapture);

    // Camera
    dlgCameraControl = new DlgSettingCamera(this);
    const MediaInfo mediaInfo = dlgCameraControl->setMediaInfo(CAM_WIDTH, CAM_HEIGHT, CAM_FPS, CAM_FORMAT);

    // btn
    connect(ui->CameraBtn, SIGNAL(clicked()), this, SLOT(mainCameraOpenClick()));
    // readFrame
    connect(dlgCameraControl, SIGNAL(readFrame(const uchar *, qint64)),
            this, SLOT(readFrame(const uchar *, qint64)));


    /**
     * @todo 这里设置Opengl？
     * width CAM_WIDTH
     * height CAM_HEIGHT
     * fps CAM_FPS
     * format CAM_FORMAT : rgb24
     */

}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::mainCameraOpenClick() {
    dlgCameraControl->exec();
}

/**
 * @brief MainWindow::readFrame @todo 这里的回调播放数据
 * @param data
 * @param startTime
 */
void MainWindow::readFrame(const uchar *data, qint64 startTime) {
    qDebug() << "m_frameData======> " << data;
}
