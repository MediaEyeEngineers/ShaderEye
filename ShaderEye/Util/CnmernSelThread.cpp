#include "CnmernSelThread.h"
#include <QVideoFrame>
#include <QCameraInfo>

/**
 * @date 2020/07/20
 * @author changyanlong github.com/numberwolf q531365872
 */

CnmernSelThread::CnmernSelThread(QObject* parent) : QObject (parent) {

}

CnmernSelThread::~CnmernSelThread() {
    emit workFinished(1);
}

void CnmernSelThread::setInput(QCameraInfo selcaminfo, MediaInfo mediaInfo) {
    m_selcaminfo = selcaminfo;
    m_mediaInfo = mediaInfo;
}

void CnmernSelThread::start1() {
    qDebug()<< "CnmernSelThread::start1" << endl;
    emit workStart();
    doWork();
}

void CnmernSelThread::doWork() {
    m_cameraSelect = new QCamera(m_selcaminfo);
    m_cameraSelect->setCaptureMode(QCamera::CaptureVideo);

    QCamera* camera = new QCamera(m_selcaminfo);
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
    m_cameraSelect->setViewfinderSettings(ViewSet);

    if (m_image != nullptr) {
        delete m_image;
        m_image = nullptr;
    }
    m_image = new CameraImage(this);
    m_image->setSource(m_cameraSelect);
    connect(m_image, SIGNAL(CaptureFrame(const QVideoFrame&)),
            this, SLOT(recvCaptureFrame(const QVideoFrame &)));

    m_cameraSelect->start();
    // Fin
    // emit workFinished(1);
}

void CnmernSelThread::recvCaptureFrame(const QVideoFrame & frame) {
    qDebug() << "recvCaptureFrame======> 1";
    emit getFrameByThread(frame);
}







