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
    char * TEST_TEXTURE_VERTEX_SHADER = (char *)SHADER(
        layout (location = 0) in vec3 pos;
        layout (location = 1) in vec3 coor;

        out vec3 outCoor;

        void main(){
            outCoor = coor;
            gl_Position = vec4(pos, 1.0);
        }
    );

    char * TEST_TEXTURE_FRAGMENT_SHADER = (char *)SHADER(
        out vec4 color;
        uniform sampler2D cameraTex;
        in vec3 outCoor;
        void main(){
            vec2 TexCoords = vec2(outCoor.x, outCoor.y);
            color = texture(cameraTex, TexCoords);
        }
    );

    Eyer::EyerGLShaderError vertexShaderError;
    Eyer::EyerGLShaderError fragmentShaderError;
    Eyer::EyerGLProgramError programError;

    glViewRender->SetShader(vertexCode, fragCode, vertexShaderError, fragmentShaderError, programError);
    // glViewRender->SetShader(TEST_TEXTURE_VERTEX_SHADER, TEST_TEXTURE_FRAGMENT_SHADER, vertexShaderError, fragmentShaderError, programError);

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
