#include "CameraController.h"
#include "ui_CameraController.h"
#include "CameraImage.h"
#include <QVideoFrame>
#include <QCameraInfo>
#include <QThread>

#include "Util/CommonSetting.h"

CameraController::CameraController(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::CameraController)
{
    ui->setupUi(this);
    this->setWindowTitle(TITLE_CAMOPEN_WIN);

    connect(ui->GetCameraBtn, SIGNAL(clicked()), this, SLOT(cameraListClick()));

    // camera List
    m_cameras = QCameraInfo::availableCameras();
    qDebug() << m_cameras.length();
    foreach (const QCameraInfo &camerasInfo, m_cameras) {
        ui->comboBox_selcamera->addItem(camerasInfo.description());
        qDebug() << "camera:" << camerasInfo.description();
        qDebug() << "name:" << camerasInfo.deviceName();
    }
    qDebug() << "Loop End" << m_cameras.length();

    if (m_cameras.length() > 0) {
        ui->GetCameraBtn->setEnabled(true);
    }
}

CameraController::~CameraController()
{
    delete ui;
}

void CameraController::cameraListClick() {
    ui->GetCameraBtn->setText("Opening...");

    int cameraIdx = ui->comboBox_selcamera->currentIndex();
    qDebug() << "currentIndex: " << cameraIdx;
    QCameraInfo selcaminfo = m_cameras.at(cameraIdx);

    QThread *m_workerThread = new QThread();
    CnmernSelThread *worker = new CnmernSelThread();
    worker->setInput(selcaminfo, m_mediaInfo);
    worker->moveToThread(m_workerThread);

    connect(m_workerThread, &QThread::started, worker, &CnmernSelThread::start1);
    connect(worker, SIGNAL(workStart()), this, SLOT(workStart()));
    connect(worker,
            SIGNAL(workFinished(int)),
            this,
            SLOT(workFinished(int)));
    connect(worker,
            SIGNAL(getFrameByThread(const QVideoFrame &)),
            this,
            SLOT(getFrameByThread(const QVideoFrame &)));

    connect(worker, &CnmernSelThread::workFinished, worker, &CnmernSelThread::deleteLater);
    connect(worker, &CnmernSelThread::workFinished, m_workerThread, &QThread::quit);
    connect(m_workerThread, &QThread::finished, m_workerThread, &QThread::deleteLater);

    m_workerThread->start();



//    m_selectedcamera = new QCamera(selcaminfo);
//    m_selectedcamera->setCaptureMode(QCamera::CaptureVideo);

//    qDebug() << "currentIndex: " << ui->comboBox_selcamera->currentIndex();
//    QCamera* camera = new QCamera(m_cameras[ui->comboBox_selcamera->currentIndex()]);
//    camera->start();

//    QList<QCameraViewfinderSettings> ViewSets = camera->supportedViewfinderSettings();
//    QCameraViewfinderSettings ViewSet = ViewSets[0];

//    // setting mediaInfo
//    ViewSet.setPixelFormat(m_mediaInfo.format); // QVideoFrame::Format_RGB24
//    QSize sizeCamera;
//    sizeCamera.setWidth(m_mediaInfo.width);
//    sizeCamera.setHeight(m_mediaInfo.height);
//    ViewSet.setResolution(sizeCamera);
//    ViewSet.setMinimumFrameRate(m_mediaInfo.fps);
//    ViewSet.setMaximumFrameRate(m_mediaInfo.fps);

//    qDebug() << "frame rate" << ViewSet.maximumFrameRate();
//    qDebug() << " pix format" << ViewSet.pixelFormat();
//    m_selectedcamera->setViewfinderSettings(ViewSet);

//    if (m_image != nullptr) {
//        delete m_image;
//        m_image = nullptr;
//    }
//    m_image = new CameraImage(this);
//    m_image->setSource(m_selectedcamera);
//    connect(m_image, SIGNAL(CaptureFrame(const QVideoFrame&)),
//            this, SLOT(recvCaptureFrame(const QVideoFrame &)));

    /*
    QThread *m_workerThread = new CnmernSelThread();
    CnmernSelThread *worker = new CnmernSelThread();
    worker->setInput(m_out420Data, m_out420Data_2nd,
                     w, h, cspace);
    worker->moveToThread(m_workerThread);

    connect(m_workerThread, &QThread::started, worker, &IQAThread::start1);
    connect(worker, SIGNAL(workStart()), this, SLOT(workStart()));
    connect(worker,
            SIGNAL(workFinished(double, double, double, double, double, double, double)),
            this,
            SLOT(workFinished(double, double, double, double, double, double, double)));

    connect(worker, &CnmernSelThread::workFinished, worker, &CnmernSelThread::deleteLater);
    connect(worker, &CnmernSelThread::workFinished, m_workerThread, &QThread::quit);
    connect(m_workerThread, &QThread::finished, m_workerThread, &QThread::deleteLater);

    m_workerThread->start();
    */
//    m_selectedcamera->start();


    done(0);
}

const MediaInfo CameraController::setMediaInfo(int w, int h, int fps, QVideoFrame::PixelFormat format) {
    // set media info
    m_mediaInfo.width = w;
    m_mediaInfo.height = h;
    m_mediaInfo.fps = fps;
    m_mediaInfo.format = format;
    return m_mediaInfo;
}

const MediaInfo CameraController::getMediaInfo() {
    return m_mediaInfo;
}

void CameraController::workStart() {

}

void CameraController::workFinished(int param1) {

}

void CameraController::getFrameByThread(const QVideoFrame &_frame)
{
    /*
    if (m_frameData != nullptr) {
        delete [] m_frameData;
        m_frameData = nullptr;
    }
    */

    int width = _frame.width();
    int height = _frame.height();
    int linesize = _frame.bytesPerLine();

    /*
    int standardLinesize = width * 3;

    // set frame
    m_frameData = new uchar[width * height * 3];
    const uchar *framePtr = _frame.bits();

    for (int i = 0; i < height; i++) {
        memcpy(m_frameData + standardLinesize * i,
               framePtr + i * linesize,
               standardLinesize);
    }
    */

    // readFrame(m_frameData, _frame.startTime());
    emit readFrame(_frame.bits(), _frame.pixelFormat(), linesize, width, height);
    qDebug() << "m_frameData======> 1";
}









