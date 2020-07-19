#ifndef DLGSETTINGCAMERA_H
#define DLGSETTINGCAMERA_H

#include <QDialog>
#include <QCamera>

#include <QList>
#include <QCameraViewfinderSettings>
class CameraImage;
namespace Ui {
class DlgSettingCamera;
}

typedef struct MediaInfo {
    int width;
    int height;
    double maxFps;
    double minFps;
    QVideoFrame::PixelFormat format;
} MediaInfo;

class DlgSettingCamera : public QDialog
{
    Q_OBJECT

public:
    explicit DlgSettingCamera(QWidget *parent = 0);
    ~DlgSettingCamera();
    MediaInfo getMediaInfo();

private slots:
    // btn click event
    void cameraListClick();
    // callback
    void recvCaptureFrame(const QVideoFrame & frame);

signals:
    void readFrame(const uchar *data, qint64 startTime);

private:
    Ui::DlgSettingCamera *ui;
    QCamera *m_selectedcamera;
    CameraImage * image;
    QList<QCameraInfo> m_cameras;
    MediaInfo m_mediaInfo;

    uchar *m_frameData = nullptr;

};

#endif // DLGSETTINGCAMERA_H
