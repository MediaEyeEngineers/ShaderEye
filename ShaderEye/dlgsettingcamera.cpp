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
        qDebug()<<"camera:" << camerasInfo.description();
        qDebug()<<"name:" << camerasInfo.deviceName();
        /*QCamera* mCamera=new QCamera(camerasInfo);  //由camerainfo创建qcamera
                       mCaptureVideoFrame=new CaptureVideoFrame(this);  //视频帧接收类,因为需要用自己写的opengl渲染,所以有了这个类,用来拿到相机的当前帧
                       connect(mCaptureVideoFrame,SIGNAL(CaptureFrame(QVideoFrame)),this,SLOT(on_captrueframecallback(QVideoFrame)));
                       mCaptureVideoFrame->setSource(mCamera);*/
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

QString PixformatToString(QVideoFrame::PixelFormat format)
{
    switch (format)
    {
    case QVideoFrame::Format_Invalid :
        return "Format_Invalid";
        break;
    case QVideoFrame::Format_ARGB32:
        return "Format_ARGB32";
        break;
    case QVideoFrame::Format_ARGB32_Premultiplied:
        return "Format_ARGB32_Premultiplied";
        break;
    case QVideoFrame::Format_RGB32:
        return "Format_RGB32";
        break;
    case QVideoFrame::Format_RGB24:
        return "Format_RGB24";
        break;
    case QVideoFrame::Format_RGB565:
        return "Format_RGB565";
        break;
    case QVideoFrame::Format_RGB555:
        return "Format_RGB555";
        break;
    case QVideoFrame::Format_ARGB8565_Premultiplied:
        return "Format_ARGB8565_Premultiplied";
        break;
    case QVideoFrame::Format_BGRA32:
        return "Format_BGRA32";
        break;
    case QVideoFrame::Format_BGRA32_Premultiplied:
        return "Format_BGRA32_Premultiplied";
        break;
    case QVideoFrame::Format_BGR32:
        return "Format_BGR32";
        break;
    case QVideoFrame::Format_BGR24:
        return "Format_BGR24";
        break;
    case QVideoFrame::Format_BGR565:
        return "Format_BGR565";
        break;
    case QVideoFrame::Format_BGR555:
        return "Format_BGR555";
        break;
    case QVideoFrame::Format_BGRA5658_Premultiplied:
        return "Format_BGRA5658_Premultiplied";
        break;

    case QVideoFrame::Format_AYUV444:
        return "Format_AYUV444";
        break;
    case QVideoFrame::Format_AYUV444_Premultiplied:
        return "Format_AYUV444_Premultiplied";
        break;
    case QVideoFrame::Format_YUV444:
        return "Format_YUV444";
        break;
    case QVideoFrame::Format_YUV420P:
        return "Format_YUV420P";
        break;
    case QVideoFrame::Format_YV12:
        return "Format_YV12";
        break;
    case QVideoFrame::Format_UYVY:
        return "Format_UYVY";
        break;
    case QVideoFrame::Format_YUYV:
        return "Format_YUYV";
        break;
    case QVideoFrame::Format_NV12:
        return "Format_NV12";
        break;
    case QVideoFrame::Format_NV21:
        return "Format_NV21";
        break;
    case QVideoFrame::Format_IMC1:
        return "Format_IMC1";
        break;
    case QVideoFrame::Format_IMC2:
        break;
    case QVideoFrame::Format_IMC3:
        return "Format_IMC3";
        break;
    case QVideoFrame::Format_IMC4:
        return "Format_IMC4";
        break;
    case QVideoFrame::Format_Y8:
        return "Format_Y8";
        break;
    case QVideoFrame::Format_Y16:
        return "Format_Y16";
        break;
    case QVideoFrame::Format_Jpeg:
        return "Format_Jpeg";
        break;

    case QVideoFrame::Format_CameraRaw:
        return "Format_CameraRaw";
        break;
    case QVideoFrame::Format_AdobeDng:
        return "Format_AdobeDng";
        break;
    case   QVideoFrame::NPixelFormats:
        return "NPixelFormats";
        break;
    default:
        break;
    }
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
//    qDebug() << "=================== Frame ======================";
//    qDebug() << "_frame.width: " << _frame.width();
//    qDebug() << "_frame.height: " << _frame.height();
//    qDebug() << "_frame.pixelFormat" << _frame.pixelFormat();
//    qDebug() << "_frame.bits" << _frame.bits();
//    qDebug() << "_frame.startTime" << _frame.startTime();

    int width = _frame.width();
    int height = _frame.height();
    int linesize = _frame.bytesPerLine();
    int standardLinesize = width * 3;

    // set frame
    m_frameData = new uchar[width * height * 3];
    const uchar *framePtr = _frame.bits();

    for (int i = 0; i < height; i++) {
        memcpy(m_frameData + standardLinesize * i,
               framePtr + i * linesize,
               standardLinesize);
    }

    readFrame(m_frameData, _frame.startTime());
    qDebug() << "m_frameData======> 1";
}









