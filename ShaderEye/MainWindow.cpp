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

    glViewCapture = new CameraGLView(this);
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

    Eyer::EyerGLShaderError vertexShaderError;
    Eyer::EyerGLShaderError fragmentShaderError;
    Eyer::EyerGLProgramError programError;

    glViewRender->SetShader(vertexCode, fragCode, vertexShaderError, fragmentShaderError, programError);
    // glViewRender->SetShader(TEST_TEXTURE_VERTEX_SHADER, TEST_TEXTURE_FRAGMENT_SHADER, vertexShaderError, fragmentShaderError, programError);

    // test log panel
    QString errorInfo;
    if (vertexShaderError.errorLen > 0) {
        errorInfo = QString("Vertex Shader Error: \n %1").arg(vertexShaderError.error.str);
    }

    if (fragmentShaderError.errorLen > 0) {
        errorInfo = QString("%1 \n Fragment Shader Error: \n %2")
                .arg(errorInfo).arg(fragmentShaderError.error.str);
    }

    if (programError.errorLen > 0) {
        errorInfo = QString("%1 \n Program Error: \n %2")
                .arg(errorInfo).arg(programError.error.str);
    }

    if (errorInfo.length() > 0) {
        // QDateTime currentDataTimeInfo = QDateTime::currentDateTime();
        // QString currentDataTimeStr = currentDataTimeInfo.toString("yyyy-MM-dd hh:mm::ss.zzz");
        compileDiglogControl->setCompileLog(errorInfo);
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
