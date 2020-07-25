#include "MainWindow.h"
#include "ui_MainWindow.h"
#include <QDateTime>

/**
 * @date 2020/07/19
 * @author changyanlong github.com/numberwolf q531365872
 */
#include "View/GLView.hpp"
#include "Util/CommonSetting.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle(TITLE_MAIN_WIN);

    glViewRender = new ShaderGLView(this);
    glViewRender->setGeometry(0, 0, 400, 400);
    ui->RenderLayout->addWidget(glViewRender);

    glViewCapture = new ShaderGLView(this);
    ui->CaptureLayout->addWidget(glViewCapture);

    // Camera
    cameraControl = new CameraController(this);
    const MediaInfo mediaInfo = cameraControl->setMediaInfo(CAM_WIDTH, CAM_HEIGHT, CAM_FPS, CAM_FORMAT);

    // btn
    connect(ui->CameraBtn, SIGNAL(clicked()), this, SLOT(mainCameraOpenClick()));
    connect(ui->RenderBtn, SIGNAL(clicked()), this, SLOT(mainRenderCompileClick()));
    // readFrame
    connect(cameraControl, SIGNAL(readFrame(const uchar *, QVideoFrame::PixelFormat, int, int, int)),
            this, SLOT(readFrame(const uchar *, QVideoFrame::PixelFormat, int, int, int)));

    // DialogCompile
    compileDiglogControl = new CompileInfoWindow(this);

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
    cameraControl->exec();
}

void MainWindow::mainRenderCompileClick() {
    QString vertexCode = ui->VertexText->toPlainText();
    QString fragCode = ui->FragText->toPlainText();

    qDebug() << vertexCode;
    qDebug() << fragCode;

    /**
     * @TODO 这里渲染编译
     */

    // test log panel
    if (true) {
        QDateTime currentDataTimeInfo = QDateTime::currentDateTime();
        QString currentDataTimeStr = currentDataTimeInfo.toString("yyyy-MM-dd hh:mm::ss.zzz");
        compileDiglogControl->setCompileLog(currentDataTimeStr);
        compileDiglogControl->show();
    }

}

/**
 * @brief MainWindow::readFrame @todo 这里的回调播放数据
 * @param data
 * @param startTime
 */
void MainWindow::readFrame(const uchar *data, QVideoFrame::PixelFormat format, int linesize, int width, int height) {
    if(format == QVideoFrame::PixelFormat::Format_ARGB32){
        int channel = 4;
        unsigned char * frameData = (unsigned char *)malloc(width * height * channel);
        for(int i=0;i<height;i++){
            memcpy(frameData + width * channel * i, data + linesize * i, width * channel);
        }

        glViewCapture->SetCameraFrame(frameData, format, linesize, width, height);
        glViewRender->SetCameraFrame(frameData, format, linesize, width, height);

        free(frameData);
    }

}
