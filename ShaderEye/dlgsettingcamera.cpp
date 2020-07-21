#include "DlgSettingCamera.h"
#include "ui_dlgsettingcamera.h"
#include "CameraImage.h"
#include <QVideoFrame>
#include <QCameraInfo>

#include "CommonSetting.h"

DlgSettingCamera::DlgSettingCamera(QWidget *parent) :
    m_selectedcamera(NULL),
    QDialog(parent),
    ui(new Ui::DlgSettingCamera)
{
    ui->setupUi(this);
    this->setWindowTitle(TITLE_CAMOPEN_WIN);

    connect(ui->btn_GetCameraList, SIGNAL(clicked()), this, SLOT(cameraListClick()));

    // camera List
    m_cameras = QCameraInfo::availableCameras();   //获取所有可以支持的camera,包括Integrated camera和uvc camera
    qDebug() << m_cameras.length();
    foreach (const QCameraInfo &camerasInfo, m_cameras) {
        ui->comboBox_selcamera->addItem(camerasInfo.description());
        qDebug() << "camera:" << camerasInfo.description();
        qDebug() << "name:" << camerasInfo.deviceName();
    }
    qDebug() << "Loop End" << m_cameras.length();

    if (m_cameras.length() > 0) {
        ui->btn_GetCameraList->setEnabled(true);
    }
}

DlgSettingCamera::~DlgSettingCamera()
{
    delete ui;
}

void DlgSettingCamera::cameraListClick() {

    qDebug() << "currentIndex: " << ui->comboBox_selcamera->currentIndex();
    QCameraInfo selcaminfo = m_cameras.at(ui->comboBox_selcamera->currentIndex());
    m_selectedcamera = new QCamera(selcaminfo);
    m_selectedcamera->setCaptureMode(QCamera::CaptureVideo);

    qDebug() << "currentIndex: " << ui->comboBox_selcamera->currentIndex();
    QCamera* camera = new QCamera(m_cameras[ui->comboBox_selcamera->currentIndex()]);
    camera->start();
    QList<QCameraViewfinderSettings> ViewSets = camera->supportedViewfinderSettings();
    QCameraViewfinderSettings ViewSet = ViewSets[0];

    // setting mediaInfo
    ViewSet.setPixelFormat(m_mediaInfo.format); // QVideoFrame::Format_RGB24
    QSize sizeCamera;
    sizeCamera.setWidth(m_mediaInfo.width);
    sizeCamera.setHeight(m_mediaInfo.height);
    ViewSet.setResolution(sizeCamera);
    ViewSet.setMinimumFrameRate(m_mediaInfo.fps);
    ViewSet.setMaximumFrameRate(m_mediaInfo.fps);

    qDebug() << "frame rate" << ViewSet.maximumFrameRate();
    qDebug() << " pix format" << ViewSet.pixelFormat();
    m_selectedcamera->setViewfinderSettings(ViewSet);



    if (m_image != nullptr) {
        delete m_image;
        m_image = nullptr;
    }
    m_image = new CameraImage(this);
    m_image->setSource(m_selectedcamera);
    connect(m_image, SIGNAL(CaptureFrame(const QVideoFrame&)),
            this, SLOT(recvCaptureFrame(const QVideoFrame &)));


    m_selectedcamera->start();

    done(0);
}

const MediaInfo DlgSettingCamera::setMediaInfo(int w, int h, int fps, QVideoFrame::PixelFormat format) {
    // set media info
    m_mediaInfo.width = w;
    m_mediaInfo.height = h;
    m_mediaInfo.fps = fps;
    m_mediaInfo.format = format;
    return m_mediaInfo;
}

const MediaInfo DlgSettingCamera::getMediaInfo() {
    return m_mediaInfo;
}

void DlgSettingCamera::recvCaptureFrame(const QVideoFrame &_frame)
{
    if (m_frameData != nullptr) {
        delete [] m_frameData;
        m_frameData = nullptr;
    }

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

    qDebug() << _frame.pixelFormat() << endl;

    int width = _frame.width();
    int height = _frame.height();
    int linesize = _frame.bytesPerLine();

    int standardLinesize = width * 4;

    // qDebug() << width << "=" << height << "=" << linesize << endl;

    // set frame
    m_frameData = new uchar[width * height * 4];
    const uchar *framePtr = _frame.bits();

    for (int i = 0; i < height; i++) {
        memcpy(m_frameData + standardLinesize * i,
               framePtr + i * linesize,
               standardLinesize);
    }

    readFrame(m_frameData, _frame.startTime());
    // qDebug() << "m_frameData======> 1";
}









