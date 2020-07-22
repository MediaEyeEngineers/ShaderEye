#ifndef DLGSETTINGCAMERA_H
#define DLGSETTINGCAMERA_H

#include <QDialog>
#include <QCamera>

#include <QList>
#include <QCameraViewfinderSettings>

#include "Util/CnmernSelThread.h"

class CameraImage;
namespace Ui {
class CameraController;
}

class CameraController : public QDialog
{
    Q_OBJECT

public:
    explicit CameraController(QWidget *parent = 0);
    ~CameraController();
    const MediaInfo setMediaInfo(int w, int h, int fps, QVideoFrame::PixelFormat format);
    const MediaInfo getMediaInfo();

private slots:
    // btn click event
    void cameraListClick();
    // callback
    void getFrameByThread(const QVideoFrame & frame);
    void workStart();
    void workFinished(int param1);

signals:
    void readFrame(const uchar *data, QVideoFrame::PixelFormat format, int linesize,int width, int height);

private:
    Ui::CameraController *ui;
    QCamera *m_selectedcamera = nullptr;
    CameraImage *m_image = nullptr;
    QList<QCameraInfo> m_cameras;
    MediaInfo m_mediaInfo;

    // uchar *m_frameData = nullptr;

};

#endif // DLGSETTINGCAMERA_H
